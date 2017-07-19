#include <fstream>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "CPUTimer.h"
#include "mynew.h"
#include "speller.h"

// uncomment line below for DOS/Windows OS.
// #define DOS

#ifdef DOS
  #include <sys\stat.h>
#else
  #include <sys/stat.h>
#endif

extern int maxRAM;
extern int currentRAM;

using namespace std;

char* readDictionary(char *filename, char **dictionary, int dictSize)
{
  int fileSize;
  char *s;
  struct stat statbuf;

  stat(filename, &statbuf);
  fileSize = statbuf.st_size;
  s = new char[fileSize + 1];
  ifstream inf(filename);
  inf.read(s, fileSize);
  inf.close();
  s[fileSize] = '\0';
  dictionary[0] = strtok(s, "\n");

  for(int i = 1; i < dictSize; i++)
    dictionary[i] = strtok(NULL, "\n\r");

  return s;
} // readDictionary

char* readDocument(char **document, int dictSize, int docSize, int seed)
{
  char *s, filename[80];
  int fileSize;
  struct stat statbuf;
  sprintf(filename, "Doc-%d-%d-%d.txt", dictSize, docSize, seed);
  stat(filename, &statbuf);
  fileSize = statbuf.st_size;
  s = new char[fileSize + 100];
  ifstream inf(filename);
  inf.read(s, fileSize);
  inf.close();
  s[fileSize] = '\0';

  document[0] = strtok(s, "\n");

  for(int i = 1; i < docSize; i++)
    document[i] = strtok(NULL, "\n\r");

  return s;
} // readDocument()

void  readWrongs(int *wrongs, int dictSize, int docSize, int seed,
  int &wrongCount)
{
  char filename[80];
  wrongCount = 0;

  sprintf(filename, "Wrongs-%d-%d-%d.txt", dictSize, docSize, seed);
  ifstream inf(filename);
  while(inf >> wrongs[wrongCount++]);

  wrongCount--;
} // readWrongs()

void checkAnswers(int wrongs[], int wrongCount, int misspelled[],
  int misspelledCount)
{
  for(int i = 0; i < wrongCount && i < misspelledCount; i++)
    if(wrongs[i] < misspelled[i])
    {
      cout << "Speller missed misspelled word # " << wrongs[i] << endl;
      return;
    }
    else
      if(wrongs[i] > misspelled[i])
      {
        cout << "Speller thought correctly spelled word # " << misspelled[i]
          << " was wrong\n";
        return;
      }

  if(wrongCount != misspelledCount)
    cout << "Speller found " << misspelledCount << " misspelled words when "
      << " there were really " << wrongCount << " misspelled words.\n";
} // checkAnswers


void cleanup(char **dictionary, char *docFilePtr, char **document, int *wrongs, int *misspelled)
{
  delete [] dictionary;
  delete [] docFilePtr;
  delete [] document;
  delete [] wrongs;
  delete [] misspelled;
} // cleanup()


int main(int argc, char* argv[])
{
  char line[80], **dictionary, **document, *dictFilePtr, *docFilePtr;
  int *wrongs, *misspelled, misspelledCount = 0, seed, dictSize, docSize,
    wrongCount, tempMaxRAM, tempCurrentRAM;
  strcpy(line, argv[1]);
  strtok(line, "-");
  dictSize = atoi(strtok(NULL, "-"));
  docSize = atoi(strtok(NULL, "-"));
  seed = atoi(strtok(NULL, "."));
  dictionary = new char*[dictSize + 3];
  dictFilePtr = readDictionary(argv[1], dictionary, dictSize);
  document = new char*[docSize + 3];
  docFilePtr = readDocument(document, dictSize, docSize, seed);
  wrongs = new int[docSize];
  readWrongs(wrongs, dictSize, docSize, seed, wrongCount);
  misspelled = new int[docSize];
  CPUTimer ct;
  maxRAM = currentRAM = 0;
  Speller *speller = new Speller(dictionary, dictSize);
  tempMaxRAM = maxRAM;
  tempCurrentRAM = currentRAM;
  delete [] dictFilePtr;
  maxRAM = tempMaxRAM;
  currentRAM = tempCurrentRAM;
  speller->check(document, docSize, misspelled, &misspelledCount);
  cout << "CPU Time: " << ct.cur_CPUTime() << " Real RAM: " << maxRAM << endl;
  checkAnswers(wrongs, wrongCount, misspelled, misspelledCount);
  cleanup(dictionary, docFilePtr, document, wrongs, misspelled);
  delete speller;
  return 0;
} // main()

