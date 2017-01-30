#ifndef _connectionDisplay_h
#define _connectionDisplay_h_h

#include "Menu.h"

class ConnectionDisplay: public Menu
{	public:
	void display1(bool SDEtat, bool CompasEtat, bool RFDEtat, unsigned short sat);
	void boutonDisplay();
    void textDisplay(bool SDEtat, bool CompasEtat, bool RFDEtat, unsigned short sat);
	void etatDisplay(bool etat);
	void satDisplay(unsigned short sat);
	private:
};
#endif
