//Programmer: Reuben French
//Description: Defines all of the Instruction class functions

#include<iostream>
#include<cctype>
#include "Instruction.h"

using namespace std;

//Constructor
Instruction::Instruction()
{
  octal = 0;
  hexA = '0';
  hexB = '0';
  hexC = '0';
};

void Instruction::setOctal(const int oct)
{
  if(((oct/1000)%10)<8 && ((oct/100)%10)<8 && ((oct/10)%10)<8 && (oct%10)<8
&& oct>=0 && oct<8888)
  {
    octal = oct;
  }
  else
  {
    cout << "Error: Cannot pass " << oct << " as octal.\n";
    exit(0);
  }
  oct2hex();
  return;
};

void Instruction::setOctalInst(const int oct)
{
  if(oct>=0 && oct<88)
  {
    setOctal((octal%100)+(100*oct));
  }
  else
  {
    cout << "Error: Cannot pass " << oct << " as octal code.\n";
    exit(0);
  }
  return;
};

void Instruction::setOctalArg(const int oct, const int arg)
{
  if(oct >= 0 && oct < 88)
  {
    if(arg == 1)
    {
      setOctal((octal/100)*100+(octal&10)+10*oct); 
    }
    else if(arg == 2)
    {
      setOctal((octal/10)*10+oct);
    }
    else
    {
      cout << arg << "is not a valid argument position.\n";
    }
  }
  else
  {
    cout << "Error: Cannot pass " << oct << " as octal argument.\n";
    exit(0);
  }
};

int Instruction::getOctal() const
{
  return octal;
};

//Note: Hex digits are ordered 012, not 210.
void Instruction::setHex(const char hex[])
{
  setHexDig(hex[0], 0);
  setHexDig(hex[1], 1);
  setHexDig(hex[2], 2);
  
  return;
};

void Instruction::setHex(const char hex1, const char hex2, const char hex3)
{
  setHexDig(hex1, 0);
  setHexDig(hex2, 1);
  setHexDig(hex3, 2);
  
  return;
};

void Instruction::setHexDig(const char hex, const int dig)
{
  if(isxdigit(hex))
  {
    if(dig==0)
    {
      hexA = hex;
    }
    else if(dig==1)
    {
      hexB = hex;
    }
    else if(dig==2)
    {
      hexC = hex;
    }
    else
    {
      cout << "Error: " << dig << " is not a valid hex position.\n";
      exit(0);
    }
  }
  else
  {
    cout << "Error: " << hex << " is not a valid hex digit.\n";
    exit(0);
  }
  
  hex2oct();
  return;
};

void Instruction::getHex(char hex[]) const
{
  hex[0] = hexA;
  hex[1] = hexB;
  hex[2] = hexC;
  
  return;
};

//length = 12
void Instruction::setPlain(const char text[])
{
  for(int i = 0; i<WORD_LENGTH; i++)
  {
    plain[i] = text[i];
  }
  return;
};

void Instruction::getPlain(char text[]) const
{
  for(int i = 0; i<WORD_LENGTH; i++)
  {
    text[i] = plain[i];
  }
  return;
};

//Calculations
void Instruction::oct2hex()
{
  int trueValue = (octal/1000)*512 + ((octal/100)%10)*64 + ((octal/10)%10)*8
+ (octal%10);

  hexC = i2xc(trueValue%16);
  trueValue /= 16;
  
  hexB = i2xc(trueValue%16);
  trueValue /= 16;
  
  hexA = i2xc(trueValue);
  
  return;
};

void Instruction::hex2oct()
{
  int trueValue = 256*xc2i(hexA)+16*xc2i(hexB)+xc2i(hexC);
  
  octal = trueValue%8;
  trueValue /= 8;
  octal = (10*octal)+(trueValue%8);
  trueValue /= 8;
  octal = (10*octal)+(trueValue%8);
  trueValue /= 8;
  octal = (10*octal)+(trueValue%8);
  
  return;
};
void Instruction::dec2oct(int dec)
{
  int oct = dec%8;
  oct = dec%8;
  dec /= 8;
  oct = (10*oct)+(dec%8);
  dec /= 8;
  oct = (10*oct)+(dec%8);
  dec/= 8;
  oct = (10*oct)+(dec%8);
  setOctal(oct);
  return;
};
void Instruction::dec2hex(int dec)
{
  hexC = i2xc(dec%16);
  dec /= 16;
  
  hexB = i2xc(dec%16);
  dec /= 16;
  
  hexA = i2xc(dec);
  
  hex2oct();
  
  return;
};

//-----PRIVATE-----
char Instruction::i2xc(const int num) const
{
  char xc;
  if(num < 10)
  {
    xc = num+'0';
  }
  else
  {
    xc = num+'a'-10;
  }
  return xc;
};

int Instruction::xc2i(const char xc) const
{
  int num;
  if(isdigit(xc))
  {
    num = xc-'0';
  }
  else if(isupper(xc))
  {
    num = xc-'A'+10;
  }
  else if(islower(xc))
  {
    num = xc-'a'+10;
  }
  return num;
};

