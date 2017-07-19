//Received Help from TA Suraj and ecs tutor Matthew Kotila 
//Also got help from TA Michael Papadopoulos 
#include "speller.h"
#include <cstring>
#include <iostream>
using namespace std;
 
Speller::Speller(char *dictionary[], int dictSize)
{    
    //Create new hash table fmakeor inserting dictionary words in it.
    //myHashTable = new QuadraticHashTable<char*> (NULL, dictSize);
    //Using a different size for our hash table since dictSize would rehash.
    //Making a fixed table size made an improvement in RAM
    myHashTable = new QuadraticHashTable<char*> (NULL, 180959);
  
    //Now we need to store the words into our hash table
    //First make a temp char pointer for each word
    int i = 0;
    
    //Then Copy the words into our temp dictionary and insert it to our hash table
    //for(; i < dictSize; i++)
    //{
    //    char* tempWord = new char[20];
    //    strncpy(tempWord, dictionary[i], 20);
    //    (*myHashTable).insert(tempWord);
    //}

    //The previous for loop did not run as fast so after optimizing it, we will
    //use a different approach that does not create a char pointer every time
    for(; i < dictSize; i++)
    {
        strcpy((*myHashTable).Word20[i].char20, dictionary[i]);
        (*myHashTable).insert((*myHashTable).Word20[i].Word());//.Word() is returning a pointer to the string in the ith position of the array of words
    }
 
}  // Speller()
 
 
Speller::~Speller()
{
    //Need to prevent memory leaks
    delete myHashTable;
} // ~Speller()
 
 
void Speller::check(char *document[], int docSize, int misspelled[],
  int *misspelledCount)
{
  *misspelledCount = 0;
  int i = 0;
  //Now we check for misspelled words in our document using our hash table's find function
  //if the word isn't found then increment the count by 1
  for(; i < docSize; i++)
    if((*myHashTable).find(document[i]) == NULL)
        misspelled[(*misspelledCount)++] = i;
 
}  // check()
 