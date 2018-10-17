//Programmer: Reuben French
//Description: Declares the Layer class

#ifndef LAYER_H
#define LAYER_H

using namespace std;

const int MAX_LAYERS = 16;

class Layer
{
  public:
    //Set & Get
    Layer();
    int getStart() const;
    char getType() const;
    
    //Return 'true' for success and 'false' for failure
    bool newLayer(const int S, const char T);
    bool endLayer();
    
    
  private:
    int start[MAX_LAYERS];
    /*
    'i' = If
    'w' = While/For
    'u' = function (when implemented)
    'p' = program
    '\0' = undefined
    */
    char type[MAX_LAYERS];
    int currentLayer;
};
    

#endif
