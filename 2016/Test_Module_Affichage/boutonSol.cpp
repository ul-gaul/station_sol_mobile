#include "boutonSol.h"

boutonSol::boutonSol(int pos1, int pos2, int pos3, int pos4, bool etatPress)
{
  mBouton1 = pos1;
  mBouton2 = pos2;
  mBouton3 = pos3;
  mBouton4 = pos4;
  mEtatPress = etatPress;

  pinMode(mBouton1, INPUT);
  pinMode(mBouton2, INPUT);
  pinMode(mBouton3, INPUT);
  pinMode(mBouton4, INPUT);
}

int boutonSol::getPress()
{
  mState1 = digitalRead(mBouton1);
  mState2 = digitalRead(mBouton2);
  mState3 = digitalRead(mBouton3);
  mState4 = digitalRead(mBouton4);
  if (mState1 == mEtatPress)
  {
    return 1;
  }
  if (mState2 == mEtatPress)
  {
    return 2;
  }
  if (mState3 == mEtatPress)
  {
    return 3;
  }
  if (mState4 == mEtatPress)
  {
    return 4;
  }
  return 0;
}
