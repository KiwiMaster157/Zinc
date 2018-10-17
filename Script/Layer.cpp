//Programmer: Reuben French
//Description: Defines the Layer class functions

#include<iostream>
#include "Layer.h"

using namespace std;

Layer::Layer()
{
  for(int i=1; i<MAX_LAYERS; i++)
  {
    start[i] = 0;
    type[i] = 0;
  }
  start[0] = 0;
  type[0] = 'p';
  
  currentLayer = 0;
  return;
};

int Layer::getStart() const
{
  return start[currentLayer];
};

char Layer::getType() const
{
  return type[currentLayer];
}

bool Layer::newLayer(const int S, const char T)
{
  //add T==u when functions are implemented
  if((T=='i' || T=='w') && currentLayer+1 < MAX_LAYERS)
  {
    currentLayer++;
    start[currentLayer] = S;
    type[currentLayer] = T;
    
    return true;
  }
  else
  {
    return false;
  }
};

bool Layer::endLayer()
{
  if(currentLayer>0)
  {
    start[currentLayer] = 0;
    type[currentLayer] = 0;
    currentLayer--;
    
    return true;
  }
  else
  {
    return false;
  }
};










