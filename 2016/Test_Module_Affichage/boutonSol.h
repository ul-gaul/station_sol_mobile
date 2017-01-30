
#ifndef boutonSol_h
#define boutonSol_h

#include "Arduino.h"

class boutonSol
{
  public:
    boutonSol(int pos1, int pos2, int pos3, int pos4, bool etatPress);
    int getPress();
  private:
    int mBouton1;
    int mBouton2;
    int mBouton3;
    int mBouton4;
    bool mEtatPress;
    int mState1;
    int mState2;
    int mState3;
    int mState4;
};

#endif

