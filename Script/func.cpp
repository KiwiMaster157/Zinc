//Programmer: Reuben French
//Description: Defines general functions for Zinc

#include<iostream>
#include<fstream>
#include<cctype>
#include<ctime>

#include "func.h"

using namespace std;

bool cStrEq(const char cStrA[], const char cStrB[])
{
  bool equal;
  int i = 0;
  
  do
  {
    equal = (cStrA[i] == cStrB[i]);
    i++;
  }while(equal && cStrA[i] != '\0');
  
  return equal;
};



config getSettings(const char configFile[])
{
  config settings;
  ifstream file;
  ofstream newFile;
  string data;
  string eq;
  file.open(configFile);
  
  //Default settings
  settings.overwrite = false;
  settings.liveReport = true;
  settings.header = true;
  
  if(file)
  {
    while(file.peek() > 0)
    {
      file >> data;
      if(data == "Overwrite")
      {
        file >> eq;
        file >> settings.overwrite;
      }
      else if(data == "Live_Report")
      {
        file >> eq;
        file >> settings.liveReport;
      }
      else if(data == "Copy_Header")
      {
        file >> eq;
        file >> settings.header;
      }
    }
    file.close();
  }
  else
  {
    cout << "File not found: " << configFile << "\nCreating new config file: \""
         << configFile << "\" with defaults:\n"
         << "Overwrite = 0" << endl
         << "Live_Report = 1" << endl
         << "Copy_Header = 1" << endl;
    
    newFile.open(configFile);
    
    newFile << "Overwrite = 0" << endl
            << "Live_Report = 1" << endl
            << "Copy_Header = 1" << endl
            << "END_OF_FILE";
    
    newFile.close();
  }
  
  return settings;
};

void getFiles(ifstream& read, ofstream& write, const config& settings)
{
  char readFileName[128];
  char writeFileName[128];

  do
  {
    cout << "File to read from: ";
	  cin.getline(readFileName, 128, '\n');
	  read.open(readFileName);
	  if(!read)
      cout << "File not found. Please double check spelling and try again."
	         << endl;
	} while(!read);
	

  cout << "File to write to: ";
	cin.getline(writeFileName, 128, '\n');
	if(settings.overwrite)
	{
	  write.open(writeFileName, fstream::trunc);
	}
	else
	{
    write.open(writeFileName, fstream::app);
  }
  
  time_t rawtime;
  time (&rawtime);
  write << "Compiling <" << readFileName << "> to <" << writeFileName
            << ">.\n" << ctime(&rawtime) << endl;
  cout << endl << "Compiling <" << readFileName << "> to <" << writeFileName
       << ">.\n" << ctime(&rawtime) << endl;
    
  return;
};

void closeFilesSuccess(ifstream& read, ofstream& write)
{
  write << "\nCompile successful!\n";
  for(int i = 0; i<LINE__LENGTH; i++)
    write.put('-');
  write.put('\n');
  
  read.close();
  write.close();
  
  return;
};

void closeFilesNotFound(ifstream& read, ofstream& write,
    const string& statement)
{
  cout << "Error!\nStatement not found: " << statement << endl
       << "Closing files and ending processes...";
  
  for(int i = 0; i<LINE__LENGTH; i++)
    write.put('-');
  write.put('\n');
  
  read.close();
  write.close();
  exit(0);
  return;
};

void closeFilesNotFound(ifstream& read, ofstream& write,
    const string& statement, const int lineNum, const int columnNum)
{
  cout << "Error!\nStatement not found: " << statement << endl
       << "Line: " << lineNum << "\tColumn: " << columnNum << endl
       << "Closing files and ending processes...";
  
  for(int i = 0; i<LINE__LENGTH; i++)
    write.put('-');
  write.put('\n');
  
  read.close();
  write.close();
  exit(0);
  return;
};




int findStart(ifstream& read, ofstream& write, const config& settings)
{
  int lineNum=1;
  int colNum = 0;
  int layer = 0;
  char word[LINE__LENGTH];
  char letter;
  bool isBegin = false;
  
  while(!isBegin)
  {
    letter = read.get();
    if(settings.header)
      write.put(letter);
      
    if(letter == ' ')
    {
      word[colNum] = '\0';
      isBegin = cStrEq(word, "BEGIN");
      colNum = 0;
    }
    else if(letter == '\n')
    {
      word[colNum] = '\0';
      isBegin = cStrEq(word, "BEGIN");
      lineNum++;
      colNum = 0;
    }
    else if(letter < 0)
    {
      closeFilesNotFound(read, write, "BEGIN");
    }
    else
    {
      word[colNum] = letter;
      colNum++;
    }
  }
  
  if(settings.liveReport)
  {
    cout << "BEGIN statement found on line " << lineNum << endl;
  }
  
  return lineNum;
};

bool readLine(ifstream& read, char line[])
{
  int i = 0;
  bool isData = false;
  
  while(read.peek() == ' ')
  {
    read.get();
  }
  
  while(read.peek() != '\n' && read.peek() > 0)
  {
    line[i] = read.get();
    i++;
    isData = true;
  }
  
  while(i<LINE__LENGTH)
  {
    line[i]=0;
    i++;
  }
  
  return isData;
};


char getWord(const char line[], int& J, char word[])
{
  int k = J;
  int p = 0;
  
  for(int i = 0; i < WORD_LENGTH; i++)
  {
    word[i]=0;
  }
  
  if(isupper(line[J]))
  {
    while(isalnum(line[J]) && J < LINE__LENGTH && p < WORD_LENGTH)
    {
      word[p]=line[J];
      J++;
      p++;
    }
    while(line[J]==' '  && J < LINE__LENGTH)
    {
      J++;
    }
    
    if(line[J] == '\0')
    {
      J = LINE__LENGTH;
    }
    
    if(line[J] == '~') return 'c';
    
    if(cStrEq(word, "Print")) return 'p';
    if(cStrEq(word, "Line")) return 'l';
    if(cStrEq(word, "If")) return 'i';
    if(cStrEq(word, "Then")) return 't';
    if(cStrEq(word, "Else")) return 'e';
    if(cStrEq(word, "While")) return 'w';
    if(cStrEq(word, "For")) return 'f';
    if(cStrEq(word, "Do")) return 'd';
    if(cStrEq(word, "End")) return 'n';
//  if(cStrEq(word, "Func")) return 'u';  
    if(cStrEq(word, "System")) return 's';
    
    for(int v=0; v<LINE__LENGTH; v++)
    {
      if(line[v] == '$')
      {
        return 'q';
      }
    }
    
    
    
    J = k;
    return 'r';
  }
  
  J++;
  return 0;
}




