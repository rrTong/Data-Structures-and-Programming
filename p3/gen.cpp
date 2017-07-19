//gen.cpp
//
//Authors: Ryan Tong, Aki Saito
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

//System Header Files
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "SplayTree.h"

using namespace std;


void toLowercase(string &str, bool chk) //makes words lowercase regardless if upper or lowercase
{
    string temp = "";
    bool check = chk;

    if(check == true)
    {
        for(int i = 0; i < str.length(); i++)
        {
            if(isalpha(str[i]))
                temp+=(tolower(str[i]));
        }
        str = temp;
    }

}


struct Word
{
public:
    string word;
    int wordNum;
    int lineNum;
};

class WordLister
{
public:
    Word w[500,000];

};

int main()
{
    WordLister wlist;
    Word w;
    int lineN = 0;

    string file;
    cout << "Which file do you want to open? ";
    getline(cin,file);

    ifstream in;
    in.open(file);

    if(!in)
    {
        cout << "No file found.\n";
        exit(0);
    }

    while(in.peek() != EOF)
    {
       string line;

       getline(in, line);
       lineN++;
       istringstream iss(line);

       while(iss.peek() != EOF)
       {
           string wordToken;
           int i = 0;
           iss.ignore(' ', 12);
           toLowercase(wordToken, true);
           wlist.w[i] = wordToken;

       }
    }








    SplayTree<int> spt(-1);

    string token;
    while(in.peek() != EOF)
    {
        string line;
        getline(in, line);
        lineN++;
        istringstream is(line);
        while(is.peek() != EOF)
        {
            is >> token;
            is.ignore(' ', 12);
            toLowercase(token);
            //var = "_____"
            Word currentWord;
            currentWord.str = token;
            cout << token;
            currentWord.wordNum = 1;
            currentWord.lineNum = lineN;
        }

    }

}
