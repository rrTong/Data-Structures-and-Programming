#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;

LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft()

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
  {
    last = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];
    // i may end up at -1
    values[i + 1] = value;
  }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
  {
    addToThis(value);
    return NULL;
  } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addToLeft(value, last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
    {
      addToRight(value, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()

////////////////////////////////////////////////////////////////////////////////////////////IM HERE
LeafNode* LeafNode::remove(int value)
{
	int pos;
	int store;
	//First we need to find if value exists

	for(pos = 0; pos < count && values[pos] != value; pos++);
	//if we found it, we need to decrease the number of elements, and remove value by shifting
	if(pos < count)
    {
        count--;
        for(int i = pos; i < count; i++)
            values[i] = values[i + 1];
    }
    //Now that we removed it, we check if we need to borrow if we need to borrow but cannot receive any, we merge
    if(count < (leafSize + 1)/2)//checks if we need to borrow
    {
        //Create a ptr for our siblings, to make it easier to deal with which sibling we're using/working with
        LeafNode *leafptr = ((LeafNode*)leftSibling);
        if(this->leftSibling != NULL)//Check if left sib exists
        {
            if(leftSibling->getCount() > (leafSize)/2)//check if borrow
                this->addToThis(leafptr->borrow(true));
            else//merge
            {
                if(leafptr->getLeftSibling())//If there is a left sib
                {
                    this->setLeftSibling(leafptr->getLeftSibling());//set the new left sib
                    leftSibling->setRightSibling(this);//set right sib
                }
                else{this->setLeftSibling(NULL);} //no left sib
                for(int j = 0; j < count; j++)
                {
                    store = leafptr->getCount();
                    values[j + store] = values[j];
                }
                for(int k = leafptr->getCount() - 1; k >= 0; k--)
                {
                    values[k] = leafptr->values[k];
                    count++;
                }
                return leafptr;
            }
        }//if there is no left sibling but right sibling exists
        else if(this->rightSibling != NULL && this->leftSibling == NULL)
        {
            leafptr = ((LeafNode*)rightSibling);//Now we need to work with right sibling
            if(rightSibling->getCount() > (leafSize)/2)//check if borrow
            {
                values[count] = leafptr->borrow(false);
                count++;
            }
            else//if merge
            {
                if(leafptr->rightSibling)//check if right sib exists
                {
                    this->setRightSibling(leafptr->getRightSibling());//set the new siblings
                    rightSibling->setLeftSibling(this);
                }
                else{this->setRightSibling(NULL);}//sets nothing to right because nothing was found


                for(int j = 0; j < leafptr->getCount(); j++)//transfer value
                {
                    values[count] = leafptr->values[j];
                    count++;
                }
                return leafptr;
            }
            //Check if the leaf is empty, if empty then returns null
            if(parent != NULL && ((count == 0)))
                return NULL;
        }
    }
	return NULL;
}

int LeafNode::borrow(bool leftOrRight)
{
    bool loR = leftOrRight;
    int temp = values[count - 1];
    count--;
    if(loR)
        return temp;
    else
    {
        temp = values[0];
        for(int i = 0; i < count; i++)
            values[i] = values[i + 1];
        return temp;
    }


}

LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);

  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

