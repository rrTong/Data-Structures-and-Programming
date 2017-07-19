//
//timetest.cpp
//

//Header Files
#include "CPUTimer.h"
#include "CursorList.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "QueueAr.h"
#include "StackAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"

//Classes
#include <iostream>
#include <string>
#include <fstream>

vector<CursorNode <int>> cursorSpace(500001);

using namespace std;

int getChoice();
void RunList(string file);
void RunCursorList(string file);
void RunStackAr(string file);
void RunStackLi(string file);
void RunQueueAr(string file);
void RunSkipList(string file);

int main()
{
    cout << "Please enter file name: ";
    string filename;
    cin >> filename;
    CPUTimer ct;
    int choice;
    do
    {
        choice = getChoice();
        ct.reset();
        switch(choice)
        {
            case 1: RunList(filename); break;
            case 2: RunCursorList(filename); break;
            case 3: RunStackAr(filename); break;
            case 4: RunStackLi(filename); break;
            case 5: RunQueueAr(filename); break;
            case 6: RunSkipList(filename); break;

        }
        cout << "CPU Time: " << ct.cur_CPUTime() << endl;
    } while (choice > 0);
    return 0;
}

int getChoice()
{
    int choice = -1;
    cout << "\n      ADT Menu"
        << "\n 0. Quit"
        << "\n 1. LinkedList"
        << "\n 2. CursorList"
        << "\n 3. StackAr"
        << "\n 4. StackLi"
        << "\n 5. QueueAr"
        << "\n 6. SkipList" << endl;
    cout << "\nYour choice >> ";
    cin >> choice;
    return choice;
}

void RunList(string file)
{
    string commentLine = "";
    ifstream infile(file);
    getline(infile, commentLine);
    char command;
    int value;

    List<int> list;
    ListItr<int> it = list.zeroth();

    while(infile >> command >> value)
    {
        if(command == 'i')
            list.insert(value,it);
        else
            list.remove(value);
    }
}

void RunCursorList(string file)
{
    string commentLine = "";
    ifstream infile(file);
    getline(infile, commentLine);
    char command;
    int value;

    CursorList<int> cList(cursorSpace);
    CursorListItr<int> cIt = cList.zeroth();

    while(infile >> command >> value)
    {
        if ( command == 'i')
            cList.insert(value, cIt);
        else
            cList.remove(value);
    }
}

void RunStackAr(string file)
{
    string commentLine = "";
    ifstream infile(file);
    getline(infile, commentLine);

    char command;
    int value;

    StackAr<int> sAr(500001);

    while(infile >> command >> value)
    {
        //cout << command << ' ' << value << endl;
        if (command == 'i')
            sAr.push(value);
        else
            sAr.pop();
    }
}

void RunStackLi(string file)
{
    string commentLine = "";
    ifstream infile(file);
    getline(infile, commentLine);

    char command;
    int value;

    StackLi<int> sLi;

    while(infile >> command >> value)
    {
        //cout << command << ' ' << value << endl;
        if (command == 'i')
            sLi.push(value);
        else
            sLi.pop();
    }
}

void RunQueueAr(string file)
{
    string commentLine = "";
    ifstream infile(file);
    getline(infile, commentLine);

    char command;
    int value;

    Queue<int> qAr(500001);

    while(infile >> command >> value)
    {
        if (command == 'i')
            qAr.enqueue(value);
        else
            qAr.dequeue();
    }
}

void RunSkipList(string file)
{
    string commentLine = "";
    ifstream infile(file);
    getline(infile, commentLine);
    char command;
    int value;

    SkipList<int> skpList(-1, 500001);

    while(infile >> command >> value)
    {
        if (command == 'i')
            skpList.insert(value);
        else
            skpList.deleteNode(value);
    }
}
