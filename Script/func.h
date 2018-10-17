//Programmer: Reuben French
//Description: Zinc general function header file

#ifndef FUNC_H
#define FUNC_H

#include<iostream>
#include<fstream>

using namespace std;

const int LINE__LENGTH = 80;
const int WORD_LENGTH = 12;
const int INST_LIST_LENGTH = 2048;

//Contains information regarding output settings
struct config
{
  bool overwrite;
  bool liveReport;
  bool header;
  
};

//Will return whether two c_strings are equal up to the first NULL character
bool cStrEq(const char cStrA[], const char cStrB[]);

//Will read configFile (default "config.txt") and return a config struct
config getSettings(const char configFile[]);

//Will open the files to be selected by the user and insert timestamp.
void getFiles(ifstream& read, ofstream& write, const config& settings);

//Will insert successful closing delimeter and close the files
void closeFilesSuccess(ifstream& read, ofstream& write);

/*
Will close files and return an error statement.

*/
void closeFilesNotFound(ifstream& read, ofstream& write, const string&);
void closeFilesNotFound(ifstream& read, ofstream& write, const string&,
                        const int lineNum, const int columnNum);

/*
Will search read for the BEGIN statement.
Depending on settings, text before the BEGIN will printed as a header.
Will return the line number of the following statement.
*/
int findStart(ifstream& read, ofstream& write, const config& settings);

/*
Will read a line from read and store it in line.
Initial indentation spaces will be removed and the end of line will be filled
  with '\0'.
Returns true if there is data on that line.
*/
bool readLine(ifstream& read, char line[]);

/*
Given a line from readLine(), will find the first word in line starting
  at position J.
Words end at spaces, the end of a line, null, and special characters, such as:
+ - * / % # = > < ,
J will be se to the start of the next word.
Returns 'q' if the line is an equation.
Returns 'c' if the line is a comment. (denoted by ~)
Returns 'p' if the word is "Print".
Returns 'l' if the word is "Line".
Returns 'i' if the word is "If".
Returns 't' if the word is "Then".
Returns 'e' if the word is "Else".
Returns 'w' if the word is "While".
Returns 'f' if the word is "For".
Returns 'd' if the word is "Do".
Returns 'n' is the word is "End".
Returns 's' if the word is "System".
Returns 'r' in the case of an error; will also return original J.
Returns '0' if there is no word;
*/
char getWord(const char line[], int& J, char word[]);




#endif


