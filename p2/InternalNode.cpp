#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
  {
    children[i + 1] = children[i];
    keys[i + 1] = keys[i];
  } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()


void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
  {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
  } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()



int InternalNode::getMaximum() const
{
  if(count > 0) // should always be the case
    return children[count - 1]->getMaximum();
  else
    return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
  {
    addToThis(ptr, pos + 1);
    return NULL;
  } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
  {
    addToLeft(last);
    return NULL;
  }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
    {
      addToRight(ptr, last);
      return NULL;
    }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)


void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


BTreeNode* InternalNode::borrow(bool leftOrRight)
{
    bool left = leftOrRight;
    BTreeNode* temp;
    if(left)
    {
        temp = children[count - 1];
        count--;
        return temp;
    }
    else
    {
        temp = children[0];
        count--;
        for(int i = 0; i < count; i++)
        {
            children[i] = children[i + 1];
            keys[i] = children[i]->getMinimum();
        }
        return temp;
    }

}

BTreeNode* InternalNode::remove(int value)
{  // to be written by students

  //First Find the position of the value to remove
  //Same as insert logic with finding value position
  int pos = 0;
  int num = count - 2;
  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  //Now we remove the value using the found position
  BTreeNode* leaf = children[pos]->remove(value);

  //After remove, we first update the node

  //Updates the current and preceding nodes
  for(int i = 0; i < count; i++)
    keys[i] = children[i]->getMinimum();

  //check if there is only one child
  if((children[pos] == leaf && count == 1))
        return this;

  //Next we need to check for any node that were merged and if they were, we need to adjust/update
  for(int i = 0; i < count; i++)
  {
      if(children[i] == leaf)
      {
          for(int pHold = i; pHold < count - 1; pHold++)
          {
              children[pHold] = children[pHold + 1];//shift
              keys[pHold] = children[pHold]->getMinimum();//update
          }
          count--;
          break;
      }
  }

  //Now we check if internal node needs to borrow or merge
  if(count < (internalSize + 1)/2)
  {
      //Create InternalNode pointers to make left and right sibling usage easier
      InternalNode* internalptrLeft = ((InternalNode*)leftSibling);
      InternalNode* internalptrRight = ((InternalNode*)rightSibling);

      //Create a BTreeNode pointer to access required values to borrow
      BTreeNode* needValue;
      int leftIntCount;
      bool Left = false;
      if(leftSibling != NULL)//check if left sibling exists
      {
          if(leftSibling->getCount() > (internalSize + 1)/2)//Check if we can borrow
          {
              needValue = internalptrLeft->borrow(true);//returns the value that was borrowed
              for(int i = count - 1; i >= 0; i--)
              {

                  children[num] = children[num + 1];//shifts
                  keys[num] = children[num]->getMinimum();//updates
              }
              count--;
          }
          //we need to merge
          else
          {
              //First merge with left sibling
              //Then we take the current values and shift it and update
              for(int i = 0; i < count; i++)
              {
                  int leafCount = i + internalptrLeft->getCount();
                  children[leafCount] = children[leafCount-internalptrLeft->getCount()];//shift
                  keys[leafCount] = children[leafCount]->getMinimum();//update
              }

              //Now we need to get the values from the merging node, and update the internal node
              for(leftIntCount = internalptrLeft->getCount() - 1; leftIntCount >= 0; leftIntCount--)
              {
                  children[leftIntCount] = internalptrLeft->children[leftIntCount];//merging
                  keys[leftIntCount] = children[leftIntCount]->getMinimum();//updating
                  count++;
              }
              //check if we have a left sibling and if true, reset their pointers to the left sibling's left sibling
              if(internalptrLeft->leftSibling)
              {
                  this->setLeftSibling(internalptrLeft->leftSibling);
                  leftSibling->setRightSibling(this);//set left sibling's right sibling to current
              }
              //if no sibling, then just reset to null
              else
              {
                  this->setLeftSibling(NULL);
              }

              return internalptrLeft;
          }
          Left = true;
      }
      //Now for if there is no left but right sibling
      else if(Left == false && rightSibling != NULL)
      {
          //Check if right sibling can give any
          if(rightSibling->getCount() > (internalSize + 1)/2)
          {
              needValue = internalptrRight->borrow(false);//returns the value that was borrowed, pass false because this is not left sibling
              children[count] = needValue;
              keys[count] = children[count]->getMinimum();//updating new minimum
              count++;
          }
          //If we can't borrow, then we merge
          else
          {
              //First we need to merge with the right sibling
              //Take the current value and shift it and update
              for(int i = 0; i < internalptrRight->getCount(); i++)
              {
                  children[count] = internalptrRight->children[i];//shifts
                  keys[count] = children[count]->getMinimum();//updates
                  count++;
              }

              //check if we have a right sibling and if true, reset their pointers to the right sibling's right sibling
              if(internalptrRight->getRightSibling() != NULL)
              {
                  this->setRightSibling(internalptrRight->getRightSibling());
                  rightSibling->setLeftSibling(this);//set right sibling's left sibling to current
              }
              //if no right sibling then just set current to NULL
              else
              {
                  this->setRightSibling(NULL);
              }

              return internalptrRight;

          }
      }

  }
  //if the node is alone then we just return a leaf(this)
  if((count == 1))
    return this;

  return NULL; // filler for stub
} // InternalNode::remove(int value)


void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMinimum(this);
      break;
    }
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()

BTreeNode* InternalNode::getLeafMin(){return children[0];}
