//Programmer: Reuben French
//Description: Declares the Instruction class

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "func.h"

using namespace std;

class Instruction
{
  public:
    //Set & Get
    Instruction();
    void setOctal(const int oct);
    void setOctalInst(const int oct);
    void setOctalArg(const int oct, const int arg);
    int getOctal() const;
    
    void setHex(const char hex[]);
    void setHex(const char hex1, const char hex2, const char hex3);
    void setHexDig(const char hex, const int dig);
    void getHex(char hex[]) const;
    
    void setPlain(const char text[]);
    void getPlain(char text[]) const;
    
    //Calculations
    //These will directly change the private members, not outpur a result
    void oct2hex();
    void hex2oct();
    void dec2oct(int dec);
    void dec2hex(int dec);
    
    void internalError();
    
  private:
    /*
    Note: octal is a decimal number that acts as an octal number.  When setting
    its value, use dec2oct() if you want to store a value instead of a literal.
    */ 
    int octal;
    char hexA;
    char hexB;
    char hexC;
    char plain[WORD_LENGTH];
    
    //Takes integer from 0-15 and returns a lowercase hex assignment
    char i2xc(const int num) const;
    //Takes a hex digit and returns its decimal value
    int xc2i(const char xc) const;
};


#endif

