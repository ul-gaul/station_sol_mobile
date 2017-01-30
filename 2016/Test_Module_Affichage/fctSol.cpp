  #include "fctSol.h"
/*
liste des actions:

1: aller � menu principal
2: aller � menu data 1
3: aller � menu data 2
4: aller � menu rep�rage
5: aller � menu set rep�rage
6: zoom rep�rage
7: unzoom rep�rage
8: aller � menu connections
9: aller � la prochaine d�cimale (set rep�rage)
10: incr�menter d�cimale (set rep�rage)
11: d�cr�menter d�cimale (set rep�rage)
*/

int fctSol::doFct(int menu, int btn)
{
  switch (menu){
    case 1:
      if (btn == 1) {
        return 2;
        //aller au menu data 2
      }
      if (btn == 2) {
        return 3;
        //aller au menu data 3
      }
      if (btn == 3) {
        return 4;
        //aller au menu du mode rep�rage
      }
      if (btn == 4) {
        return 8;
        // aller au menu des connections
      }
      case 2:
        if (btn == 1) {
        return 1;
        //retourner au menu principal
      }
      if (btn == 2) {
        return 12;
        //aller au menu data 3
      }
      if (btn == 3) {
        return 3;
        //aller au menu data 2
      }
      if (btn == 4) {
        return 1;
        //retourner au menu principal
      }
      case 3:
      if (btn == 1) {
        return 1;
        //retourner au menu principal
      }
      if (btn == 2) {
        return 2;
        //aller au menu data 1
      }
      if (btn == 3) {
        return 12;
        //aller au menu data 3
      }
      if (btn == 4) {
        return 1;
        //retourner au menu principal
      }
      case 4:
      if (btn == 1) {
        return 5;
        //aller au menu set rep�rage
      }
      if (btn == 2) {
        return 6;
        //faire un zoom dur l'�chelle rep�rage
      }
      if (btn == 3) {
        return 7;
        //faire un unzoom sur l'�chelle rep�rage
      }
      if (btn == 4) {
        return 1;
        //retourner au menu principal
      }
      case 5: // menu set rep�rage
      if (btn == 1) {
        return 9;
        //aller � la prochaine d�cimale
      }
      if (btn == 2) {
        return 10;
        //incr�menter d�cimale (set rep�rage)
      }
      if (btn == 3) {
        return 11;
        //d�cr�menter d�cimale (set rep�rage)
      }
      if (btn == 4) {
        return 4;
        //retourner au menu rep�rage
      }

      case 7:
      if (btn == 1) {
        return 1;
        //retourner au menu principal
      }
      if (btn == 2) {
        return 3;
        //aller au menu data 2
      }
      if (btn == 3) {
        return 2;
        //aller au menu data 1
      }
      if (btn == 4) {
        return 1;
        //retourner au menu principal
      }

}
return 1; //Si un bouton est pressé, mais qu'il n'est pas identifié
}
