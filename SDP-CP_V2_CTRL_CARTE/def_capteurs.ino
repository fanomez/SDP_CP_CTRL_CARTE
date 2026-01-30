// fichier de backup
// DEFINITION DES CAPTEURS DANS variables_globales_basic.h

#include "definition_banque.h"
#include "variables_globales.h"
#include "variables_globales_basic.h"

/* non utilisé ======================================
// Rempli le tableau contenant les différents types de capteurs
void defintion_capteur (uint8_t  Numero, uint16_t Var0 , uint16_t Var1 , uint16_t Var2, uint16_t Var3 , uint16_t Var4){
  Var_capteur[Numero][0]=Var0;
  Var_capteur[Numero][1]=Var1;
  Var_capteur[Numero][2]=Var2;
  Var_capteur[Numero][3]=Var3;
  Var_capteur[Numero][4]=Var4;
}

// Défini les caractèristiques des capteurs
// (Tableau modifiable en fonction des capteurs utilisés)
void liste_capteurs(void){
  //                n_type     SaturH  SaturB  Absence  DeriveH   DeiveB        Continu
  defintion_capteur(     0,    65535,       0,      0,    65535,       0);//,    65535)    //type 0 Sans
  defintion_capteur(     1,    65535,       0,      0,     3200,    2800);//,       40)    //type 1 ABB(sans CTRL)
  defintion_capteur(     2,     5000,    1000,    500,     3200,    2800);//,       40)  //type 2 ABB
  defintion_capteur(     3,     4375,     625,    300,    2600,     2400);//,    65535)  //type 3 HASS-xxS
  
  defintion_capteur( 4,  65535,  0,    0,    65535,  0);//,   65535)    //type 4 vide
  defintion_capteur( 5,  65535,  0,    0,    65535,  0);//,   65535)    //type 5 vide
  defintion_capteur( 6,  65535,  0,    0,    65535,  0);//,   65535)    //type 6 vide
  defintion_capteur( 7,  65535,  0,    0,    65535,  0);//,   65535)    //type 7 vide
  defintion_capteur( 8,  65535,  0,    0,    65535,  0);//,   65535)    //type 8 vide
  defintion_capteur( 9,  65535,  0,    0,    65535,  0);//,   65535)    //type 9 vide
  defintion_capteur( 10, 65535,  0,    0,    65535,  0);//,   65535)    //type 10 vide
  defintion_capteur( 11, 65535,  0,    0,    65535,  0);//,   65535)    //type 11 vide
  defintion_capteur( 12, 65535,  0,    0,    65535,  0);//,   65535)    //type 12 vide
  defintion_capteur( 13, 65535,  0,    0,    65535,  0);//,   65535)    //type 13 vide
  defintion_capteur( 14, 65535,  0,    0,    65535,  0);//,   65535)    //type 14 vide
  defintion_capteur( 15, 65535,  0,    0,    65535,  0);//,   65535)    //type 15 vide

}
// ==========================================       */              
