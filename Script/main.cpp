//Programmer: Reuben French
//Description: Zinc main

#include<iostream>
#include<fstream> 
#include "func.h"
#include "Instruction.h"
#include "Layer.h"

using namespace std;


int main()
{
  ifstream readFile;
  ofstream writeFile;
  config settings;
  
  Instruction code[INST_LIST_LENGTH];
  int Inst = 0;
  
  Layer level;
  
  char Line[LINE__LENGTH] = "\0";
  char wordLiteral[WORD_LENGTH];
  char word;
  int currentLine;
  int position;
  int whileAddr;
  bool isData;
  
  settings = getSettings("config.txt");
  getFiles(readFile, writeFile, settings);
  
  currentLine = findStart(readFile, writeFile, settings);
  
  position = 0;
  
  while(!cStrEq(Line, "End"))
  {
    isData = readLine(readFile, Line);
    
    if(isData)
    {
      word = getWord(Line, position, wordLiteral);
      
      switch(word)
      {
        case 'p'://Print
          if(settings.liveReport)
          {
            cout << "Print: ";
          }
          for(int i = position; i < LINE__LENGTH; i++)
          {
            code[Inst].dec2hex(2304+Line[i]);
            if(settings.liveReport)
            {
              cout << Line[i];
            }
            Inst++;
          }
          if(settings.liveReport)
          {
            cout << endl;
          }
          break;
        case 'l'://Line
          code[Inst].setHex("90a");
          Inst++;
          if(settings.liveReport)
          {
            cout << "New Line" << endl;
          }
          break;
        case 'i'://If
          
          break;
        case 't'://Then
          code[Inst].setOctal(2762);
          Inst++;
          code[Inst].setHex("600");
          Inst ++;
          level.newLayer(Inst, 'i');
          Inst++;
          break;
        case 'e'://Else
          
          break;
        case 'w'://While
          whileAddr = Inst;
          
          break;
        case 'f'://For
          
          break;
        case 'd'://Do
          
          break;
        case 'n'://End
          
          break;
        case 'c'://comment (~)
          
          break;
        case 'q'://Equation
//          equationParser(
          break;
        case 'r'://ERROR
          cout << "Error: Undefined term \"" << wordLiteral << "\"" << endl
               << "Line: " << currentLine << "; Column: " << position << endl
               << "Closing files and processes...";
          readFile.close();
          writeFile.close();
          return 0;
          break;
        case 's'://System
          while(Line[position] != '\0' && position < LINE__LENGTH)
          {
            code[Inst].setHex(Line[position], Line[position+1],
Line[position+2]);
            if(settings.liveReport)
            {
              cout << "System code: " << Line[position] << Line[position+1]
                   << Line[position+2] << endl;
            }
            position += 4;
            Inst++;
          }
          break;
      }
    }
    else
    {
      position = 0;
      currentLine++;
    }
  }
  
  
  
  
  closeFilesSuccess(readFile, writeFile);
  
  return 0;
}
