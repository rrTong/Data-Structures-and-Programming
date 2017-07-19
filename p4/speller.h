#ifndef SPELLER_H
#define SPELLER_H
 
#include "QuadraticProbing.h"
class Speller
{
public:
  Speller(char *dictionary[], int dictSize);
  ~Speller();
  void check(char *document[], int docSize, int misspelled[], int *misspelledCount);
  //End of Public member
private:
    //Since we are using hash tables we need to declare it here, this must be in char* since we pass character pointers
    QuadraticHashTable<char*> *myHashTable;
    //End of Private member
}; // class Speller
 
 
#endif
