#pragma once



// ====== Banque EEPROM ==========
// Définition des adresses des valeurs des banques D, T, P et M
// Utilisé dans la sauvegarde des données dans l'EEPROM

#define DG 5

// DEFINE ADRESSE EEPROM
#define BanqueD 1
#define BanqueWM 2


// Adresse D

#define D_Consigne_Puis_1_Modbus_C1   0
#define D_Consigne_Puis_1_Modbus_C2   1 
#define D_Consigne_Puis_1_Modbus_C3   700 

#define D_Consigne_Temps_Modbus_C1    2 
#define D_Consigne_Temps_Modbus_C2    3 
#define D_Consigne_Temps_Modbus_C3    701 

#define D_Consigne_Puis_2_Modbus_C1   4 
#define D_Consigne_Puis_2_Modbus_C2   5
#define D_Consigne_Puis_2_Modbus_C3   702

//#define D_6                         6 
#define D_Tps_Pre_arrosage_MODBUS     7 
#define D_Tps_Fin_arrosage_MODBUS     8
#define D_MODE                        9 
//   Entrees/sorties analogique et config------------------------------------------------------        
#define D_Sortie_analogique_V1      10  
#define D_Entree_ana_efficace_V1    11  
#define D_Entree_ana_crete_V1       12  
#define D_Entree_ana_moyen_V1       13 
#define D_Entree_ana_min_V1         14  
#define D_Entree_ana_max_V1         15 
#define D_Potard_V3_Temps_old       16 
#define D_Potard_V4_Puissance_old   17  
#define D_Potard_V3_Temps           18  
#define D_Potard_V4_Puissance       19 

#define D_Sortie_analogique_V2      20  
#define D_Entree_ana_efficace_V2    21  
#define D_Entree_ana_crete_V2       22  
#define D_Entree_ana_moyen_V2       23  
#define D_Entree_ana_min_V2         24  
#define D_Entree_ana_max_V2         25 
#define D_Mesure_Simulee_C1         26 

// Define ci-dessous utilisé pour le passage de gamme (V1-V2)
#define D_Entree_ana_efficace_V7    27  
#define D_Entree_ana_crete_V7       28 
#define D_Entree_ana_moyen_V7       29 

#define D_Sortie_analogique_V3      30 
#define D_Entree_ana_efficace_V3    31
#define D_Entree_ana_crete_V3       32 
#define D_Entree_ana_moyen_V3       33 
#define D_Entree_ana_min_V3         34 
#define D_Entree_ana_max_V3         35 
#define D_Mesure_Simulee_C2         36  

// Define ci-dessous utilisé pour le passage de gamme (V3-V4)
#define D_Entree_ana_efficace_V8    37  
#define D_Entree_ana_crete_V8       38  
#define D_Entree_ana_moyen_V8       39  

#define D_Sortie_analogique_V4      40  
#define D_Entree_ana_efficace_V4    41  
#define D_Entree_ana_crete_V4       42 
#define D_Entree_ana_moyen_V4       43  
#define D_Entree_ana_min_V4         44  
#define D_Entree_ana_max_V4         45  


#define D_Entree_ana_efficace_V5    728 
#define D_Entree_ana_crete_V5       729 
#define D_Entree_ana_moyen_V5       730  
#define D_Entree_ana_min_V5         731  
#define D_Entree_ana_max_V5         732  


#define D_Entree_ana_efficace_V6    733  
#define D_Entree_ana_crete_V6       734 
#define D_Entree_ana_moyen_V6       735  
#define D_Entree_ana_min_V6         736  
#define D_Entree_ana_max_V6         737  

#define D_Entree_ana_efficace_V9    738  
#define D_Entree_ana_crete_V9       739 
#define D_Entree_ana_moyen_V9       740 


#define D_Pointeur_Mesure_Second_C1 46  
#define D_Pointeur_Mesure_Second_C2 47 
#define D_Pointeur_Mesure_Second_C3 742

#define D_I_max_REF_OLD_C1          48  

#define D_Etalonnage_X1         50 
#define D_Etalonnage_X2         51  
#define D_Etalonnage_Y1         52  
#define D_Etalonnage_Y2         53 
#define D_I_MAX_LU_C1         54 
#define D_I_MAX_LU_C2         55 
#define D_Temps_Pb_puissance        56
#define D_Periode_Fth               57     
#define D_Seuil_Ctrl_Temperature    58 
#define D_Gain_BOOST            59  
#define D_Pointeur_TOR_S1       60  
#define D_Pointeur_TOR_S2       61  
#define D_Pointeur_TOR_S3       62  
#define D_Pointeur_TOR_S4       63
#define D_COEF_CONE_TUBE        64  
#define D_Types_Capteurs        65  
#define D_Pointeur_ACQ          66  
#define D_Pointeur_DEMAG        67  
#define D_Pointeur_DCY          68 
#define D_Pointeur_ACY          69  
//     Cycle1--------------------------------------------------------------
#define  D_I_thermique_C1       70  
#define  D_Pointeur_Puissance_2_C1  71  
#define  D_Pointeur_Puissance_C1    72  
#define  D_Pointeur_Temps_C1        73  
#define  D_Pointeur_mesure_C1       74   
#define  D_U_MIN_C1           75 
#define  D_U_MAX_C1           76  
#define  D_GP_C1              77  
#define  D_I_MAX_C1           78  
#define  D_Seuil_mesure_I_C1      79  
//     Cyle2--------------------------------------------------------------
#define  D_I_thermique_C2           80  
#define  D_Pointeur_Puissance_2_C2  81  
#define  D_Pointeur_Puissance_C2    82  
#define  D_Pointeur_Temps_C2        83  
#define  D_Pointeur_mesure_C2       84 
#define  D_U_MIN_C2           85 
#define  D_U_MAX_C2           86 
#define  D_GP_C2              87 
#define  D_I_MAX_C2           88  
#define  D_Seuil_mesure_I_C2      89  
//   Cycle1&2 --------------------------------------------------------------
#define  D_KD_C1                90 
#define  D_KD_C2                91 
#define  D_Seuil_CTRL_BO_C1     92  
#define  D_Seuil_CTRL_BO_C2     93 
#define  D_Nb_val_stab_mesure_C1    94  
#define  D_Nb_val_stab_mesure_C2    95  
#define  D_Pointeur_FO_C1       96  
#define  D_Pointeur_FO_C2       97  
#define  D_Pointeur_ET_C1       98  
#define  D_Pointeur_ET_C2       99 
// ------- Cyle 3 --------------------------------------------------------------
#define  D_Pointeur_mesure_C3   104     

// -----------------------------------------------------------------------------


const uint8_t D_Mesure_simulee_C[3]     ={0,D_Mesure_Simulee_C1,D_Mesure_Simulee_C2};

const uint16_t D_Mesure_eff_V[10]         ={0,D_Entree_ana_efficace_V1,D_Entree_ana_efficace_V2,D_Entree_ana_efficace_V3,D_Entree_ana_efficace_V4,D_Entree_ana_efficace_V7,D_Entree_ana_efficace_V8,D_Entree_ana_efficace_V5,D_Entree_ana_efficace_V6,D_Entree_ana_efficace_V9};
const uint16_t D_Mesure_cre_V[10]         ={0,D_Entree_ana_crete_V1,D_Entree_ana_crete_V2,D_Entree_ana_crete_V3,D_Entree_ana_crete_V4,D_Entree_ana_crete_V7,D_Entree_ana_crete_V8,D_Entree_ana_crete_V5,D_Entree_ana_crete_V6,D_Entree_ana_crete_V9};
const uint16_t D_Mesure_moy_V[10]         ={0,D_Entree_ana_moyen_V1,D_Entree_ana_moyen_V2,D_Entree_ana_moyen_V3,D_Entree_ana_moyen_V4,D_Entree_ana_moyen_V7,D_Entree_ana_moyen_V8,D_Entree_ana_moyen_V5,D_Entree_ana_moyen_V6,D_Entree_ana_moyen_V9};

const uint16_t D_Mesure_min_V[7]         ={0,D_Entree_ana_min_V1,D_Entree_ana_min_V2,D_Entree_ana_min_V3,D_Entree_ana_min_V4,D_Entree_ana_min_V5,D_Entree_ana_min_V6};
const uint16_t D_Mesure_max_V[7]         ={0,D_Entree_ana_max_V1,D_Entree_ana_max_V2,D_Entree_ana_max_V3,D_Entree_ana_max_V4,D_Entree_ana_max_V5,D_Entree_ana_max_V6};
const uint16_t D_Pointeur_mesure_sec_C[4]  ={0,D_Pointeur_Mesure_Second_C1,D_Pointeur_Mesure_Second_C2,D_Pointeur_Mesure_Second_C3};

const uint8_t D_Puiss_MODBUS_C[3]         ={0,D_Consigne_Puis_1_Modbus_C1,D_Consigne_Puis_1_Modbus_C2};
const uint8_t D_Temps_MODBUS_C[3]         ={0,D_Consigne_Temps_Modbus_C1,D_Consigne_Temps_Modbus_C2};
const uint8_t D_Puiss2_MODBUS_C[3]        ={0,D_Consigne_Puis_2_Modbus_C1,D_Consigne_Puis_2_Modbus_C2};
const uint8_t D_Pointeur_TOR_S[5]         ={0,D_Pointeur_TOR_S1,D_Pointeur_TOR_S2,D_Pointeur_TOR_S3,D_Pointeur_TOR_S4};
const uint8_t D_I_thermique_C[3]          ={0,D_I_thermique_C1,D_I_thermique_C2};
const uint8_t D_Pointeur_Puissance_2_C[3] ={0,D_Pointeur_Puissance_2_C1,D_Pointeur_Puissance_2_C2};
const uint8_t D_Pointeur_Puissance_C[3]   ={0,D_Pointeur_Puissance_C1,D_Pointeur_Puissance_C2};
const uint8_t D_Pointeur_Temps_C[3]       ={0,D_Pointeur_Temps_C1,D_Pointeur_Temps_C2};

const uint16_t D_Pointeur_mesure_C[4]      ={0,D_Pointeur_mesure_C1,D_Pointeur_mesure_C2,D_Pointeur_mesure_C3};

const uint8_t D_U_MIN_C[3]            ={0,D_U_MIN_C1,D_U_MIN_C2};
const uint8_t D_U_MAX_C[3]            ={0,D_U_MAX_C1,D_U_MAX_C2};
const uint8_t D_GP_C[3]               ={0,D_GP_C1,D_GP_C2};
const uint8_t D_I_MAX_C[3]            ={0,D_I_MAX_C1,D_I_MAX_C2};
const uint8_t D_I_MAX_LU_C[3]         ={0,D_I_MAX_LU_C1,D_I_MAX_LU_C2};
const uint8_t D_Seuil_mesure_I_C[3]   ={0,D_Seuil_mesure_I_C1,D_Seuil_mesure_I_C2};
const uint8_t D_KD_C[3]               ={0,D_KD_C1,D_KD_C2};
const uint8_t D_Seuil_CTRL_BO_C[3]    ={0,D_Seuil_CTRL_BO_C1,D_Seuil_CTRL_BO_C2};
const uint8_t D_Nb_val_stab_mesure_C[3] ={0,D_Nb_val_stab_mesure_C1,D_Nb_val_stab_mesure_C2};
const uint8_t D_Pointeur_FO_C[3]        ={0,D_Pointeur_FO_C1,D_Pointeur_FO_C2};
const uint8_t D_Pointeur_ET_C[3]        ={0,D_Pointeur_ET_C1,D_Pointeur_ET_C2};

// Adresse WM
#define BITS_CONFIG_G1 12
#define BITS_CONFIG_G2 13

//Adresse T 

#define   T_TEMPO_SUP_ARRET_C1_SIMUL  0   
#define   T_TEMPO_1_FO_C1           1 
#define   T_TEMPO_REMANENCE_MESURES 2 
#define   T_TEMPO_REMANENCE_CMD_1   3 
#define   T_TEMPO_REMANENCE_CMD_2   4 
#define   T_TEMPO_TIME_OUT_C1     5 
#define   T_TEMPO_TIME_OUT_C2     6 
#define   T_TEMPO_TPS_MAG_C1      7
#define   T_TEMPO_TPS_MAG_C2      8
#define   T_TEMPO_SEUIL_BO_DEMAG_C1 9
#define   T_TEMPO_SEUIL_BO_DEMAG_C2 10
#define   T_TEMPO_PROB_PUISSANCE_C1 11  
#define   T_TEMPO_PROB_PUISSANCE_C2 12 
#define   T_TEMPO_PRE_SEUIL_C1      13  
#define   T_TEMPO_PRE_SEUIL_C2      14  
#define   T_TEMPO_AUTO_REGLAGE_C1   15  
#define   T_TEMPO_AUTO_REGLAGE_C2   16 
#define   T_TEMPO_DLY_PRES_COURANT_1 17 
#define   T_TEMPO_DLY_PRES_COURANT_2 18 
#define   T_TEMPO_RAMPE2_BO_C1      19  
#define   T_TEMPO_RAMPE2_BO_C2      20  
#define   T_TEMPO_RAMPE3_BO_C1      21  
#define   T_TEMPO_RAMPE3_BO_C2      22 
#define   T_TEMPO_PROB_PUISS_2_C1   23 
#define   T_TEMPO_PROB_PUISS_2_C2   24 
#define   T_TEMPO_SECU_VIGITHERM_1  25 
#define   T_TEMPO_SECU_VIGITHERM_2  26 
#define   T_TEMPO_2_FO_C1       27  
#define   T_TEMPO_1_FO_C2       28 
#define   T_TEMPO_2_FO_C2       29  
#define   T_TEMPO_MESURE_HORS_CMD_1 30  
#define   T_TEMPO_MESURE_HORS_CMD_2 31 
#define   T_TEMPO_PROB_PUISS_3_C1   32 
#define   T_TEMPO_PROB_PUISS_3_C2   33 
#define   T_TEMPO_STABILITE_INF_1   34  
#define   T_TEMPO_STABILITE_SUP_1   35 
#define   T_TEMPO_STABILITE_INF_2   36 
#define   T_TEMPO_STABILITE_SUP_2   37 
#define   T_TEMPO_DEFAUT_TETES      38 
#define   T_TEMPO_DEFAUT_TETES_2    39 
#define   T_TEMPO_MODE_ESCLAVE      40 
#define   T_TEMPO_OFFSET_AUTO         41 
#define   T_TEMPO_TPS_MAG_Preci_C1    42 
#define   T_TEMPO_TPS_MAG_Preci_C2    43 
#define   T_TIMER_Facteur_thermique   44 
#define   T_TEMPO_PROB_PUISS_4_C1     45 
#define   T_TEMPO_PROB_PUISS_4_C2     46 
#define   T_TEMPO_STABILITE_MESURE_C1 47
#define   T_TEMPO_STABILITE_MESURE_C2 48 
//#define T_49                49
//---------------------------------------------  
#define   T_Cons_Puiss1_EnCours_C1    50 
#define   T_Nb_cycle_manquant_Tps_C1  51 
#define   T_Cons_Puiss1_EnCours_C2    52  
#define   T_Nb_cycle_manquant_Tps_C2  53 
#define   T_Cons_Puiss2_EnCours_C1  54  
#define   T_Cons_Puiss2_EnCours_C2  55  
#define   T_preci_rampe_demag_C1    56  
#define   T_preci_rampe_demag_C2    57  
#define   T_Cons_Puiss1_Memo_C1     58 
#define   T_Cons_Puiss1_Memo_C2     59 

#define   T_OFFSET_CAPTEUR_V1       60  
#define   T_OFFSET_CAPTEUR_V2       61 
#define   T_Gain_P_en_cours_C1      62  
#define   T_Gain_P_en_cours_C2      63  
#define   T_COEF_CONE_TUBE_en_cours   64 
#define   T_Temps_pb_puissance_cycle  65 
#define   T_Bruit_simule            66  
#define   T_Temps_Facteur_thermique 67 
#define   T_OFFSET_CAPTEUR_V3       68  
#define   T_OFFSET_CAPTEUR_V4       69 

#define   T_Seuil_saturation_haut_V1  70 
#define   T_Seuil_saturation_bas_V1   71  
#define   T_Seuil_Presenc_capteur_V1  72  
#define   T_Seuil_derive_haut_V1      73  
#define   T_Seuil_derive_bas_V1       74  
#define   T_Seuil_saturation_haut_V2  75 
#define   T_Seuil_saturation_bas_V2   76 
#define   T_Seuil_Presenc_capteur_V2  77  
#define   T_Seuil_derive_haut_V2      78 
#define   T_Seuil_derive_bas_V2       79 

#define   T_Seuil_saturation_haut_V3  80 
#define   T_Seuil_saturation_bas_V3   81 
#define   T_Seuil_Presenc_capteur_V3  82
#define   T_Seuil_derive_haut_V3      83 
#define   T_Seuil_derive_bas_V3       84 
#define   T_Seuil_saturation_haut_V4  85 
#define   T_Seuil_saturation_bas_V4   86 
#define   T_Seuil_Presenc_capteur_V4  87  
#define   T_Seuil_derive_haut_V4      88 
#define   T_Seuil_derive_bas_V4       89 

#define   T_Seuil_saturation_haut_V5  128 
#define   T_Seuil_saturation_bas_V5   129 
#define   T_Seuil_Presenc_capteur_V5  130
#define   T_Seuil_derive_haut_V5      131 
#define   T_Seuil_derive_bas_V5       132 
#define   T_Seuil_saturation_haut_V6  133 
#define   T_Seuil_saturation_bas_V6   134 
#define   T_Seuil_Presenc_capteur_V6  135  
#define   T_Seuil_derive_haut_V6      136
#define   T_Seuil_derive_bas_V6       137 

//---------------------------------------------                      
#define   T_TEMPO_ABSENCE_CAPTEUR_V1  90
#define   T_TEMPO_ABSENCE_CAPTEUR_V2  91  
#define   T_TEMPO_ABSENCE_CAPTEUR_V3  92 
#define   T_TEMPO_ABSENCE_CAPTEUR_V4  93 
#define   T_TEMPO_SATUR_CAPTEUR_V1    94 
#define   T_TEMPO_SATUR_CAPTEUR_V2    95 
#define   T_TEMPO_SATUR_CAPTEUR_V3    96 
#define   T_TEMPO_SATUR_CAPTEUR_V4    97 
//#define  T_98              98 
//#define  T_99              99  

const uint16_t T_TEMPO_TPS_MAG_C[3]      ={0,T_TEMPO_TPS_MAG_C1,T_TEMPO_TPS_MAG_C2};
const uint16_t T_Seuil_Saturation_H[6]   ={T_Seuil_saturation_haut_V1,T_Seuil_saturation_haut_V2,T_Seuil_saturation_haut_V3,T_Seuil_saturation_haut_V4,T_Seuil_saturation_haut_V5,T_Seuil_saturation_haut_V6};
const uint16_t T_Seuil_Saturation_B[6]   ={T_Seuil_saturation_bas_V1,T_Seuil_saturation_bas_V2,T_Seuil_saturation_bas_V3,T_Seuil_saturation_bas_V4,T_Seuil_saturation_bas_V5,T_Seuil_saturation_bas_V6};
const uint16_t T_Seuil_Presence[6]       ={T_Seuil_Presenc_capteur_V1,T_Seuil_Presenc_capteur_V2,T_Seuil_Presenc_capteur_V3,T_Seuil_Presenc_capteur_V4,T_Seuil_Presenc_capteur_V5,T_Seuil_Presenc_capteur_V6};
const uint16_t T_Seuil_Derive_H[6]       ={T_Seuil_derive_haut_V1,T_Seuil_derive_haut_V2,T_Seuil_derive_haut_V3,T_Seuil_derive_haut_V4,T_Seuil_derive_haut_V5,T_Seuil_derive_haut_V6};
const uint16_t T_Seuil_Derive_B[6]       ={T_Seuil_derive_bas_V1,T_Seuil_derive_bas_V2,T_Seuil_derive_bas_V3,T_Seuil_derive_bas_V4,T_Seuil_derive_bas_V5,T_Seuil_derive_bas_V6};

//Adresse M

#define M_TIME_OUT_CYCLE_1          0
#define M_TIME_OUT_CYCLE_2          1
#define M_MESURE_HORS_COMMANDE_1    2
#define M_MESURE_HORS_COMMANDE_2    3
#define M_TEMPERATURE_0             4
#define M_TEMPERATURE_1             5
#define M_TIME_OUT_PROB_PUISSANCE_1 6
#define M_TIME_OUT_PROB_PUISSANCE_2 7
#define M_SATURATION_V1             8
#define M_SATURATION_V2             9
#define M_SATURATION_V3           10
#define M_SATURATION_V4           11
#define M_ABSENCE_CAPTEUR_V1      12
#define M_ABSENCE_CAPTEUR_V2      13
#define M_ABSENCE_CAPTEUR_V3      14
#define M_ABSENCE_CAPTEUR_V4      15

#define M_DEFAUT_TETES          16
#define M_COM_ERR               17
#define M_DEFAUT_THERMIQUE      18
#define M_DEFAUT_THERMIQUE_2      19
#define M_STABILITE_SUP_1         20
#define M_STABILITE_SUP_2         21
#define M_STABILITE_INF_1         22
#define M_STABILITE_INF_2         23
#define M_DEFAUT_FORME_ONDE_1     24
#define M_DEFAUT_FORME_ONDE_2     25
#define M_DEFAUT_TETES_2          26
#define M_COM_ERR_2               27
#define M_DERIVE_CAPTEUR_V1       28
#define M_DERIVE_CAPTEUR_V2       29
#define M_DERIVE_CAPTEUR_V3       30
#define M_DERIVE_CAPTEUR_V4       31

#define M_FACTEUR_THERMIQUE_1      32
#define M_FACTEUR_THERMIQUE_2      33
#define M_TEMPERATURE_2          34
#define M_TEMPERATURE_3          35
#define M_CAPTEUR_TEMPERATURE_0    36
#define M_CAPTEUR_TEMPERATURE_1    37
/*#define M_CAPTEUR_TEMPERATURE_2  38
#define M_CAPTEUR_TEMPERATURE_3    39
#define M_                 40
#define M_                 41
#define M_                 42
#define M_                 43
#define M_                 44
#define M_                 45
#define M_                 46
#define M_                 47  */

#define M_SORTIE_DEMAG_EN_COURS   48  
#define M_SORTIE_ALARME           49    
#define M_SORTIE_MAG_EN_COURS     50    
#define M_SORTIE_SAT              51      
#define M_SORTIE_ARROSAGE         52
#define M_SORTIE_RAMPE_DEMAG      53  
#define M_SORTIE_STABLITE_MESURES 54    
#define M_MODE_ESCLAVE          55
#define M_PRECENCE_DC_C1        56  
#define M_PRECENCE_DC_C2        57    

#define M_MESURE_EFF_1          58    
#define M_MESURE_EFF_2          59 
#define M_MESURE_EFF_3          241 


#define M_MESURE_CRETE_1        60
#define M_MESURE_CRETE_2        61  
#define M_MESURE_CRETE_3        242  

#define M_FO_MESURE_1           62    
#define M_FO_MESURE_2           63    
#define M_FO_MESURE_3           243    


#define M_INITIALISE            64
#define M_CYCLE_GENERAL_A_0     65
#define M_CYCLE_EN_COURS_1      66
#define M_CYCLE_EN_COURS_2      67
#define M_CYCLE_EN_COURS_1_DEMAG  68
#define M_CYCLE_EN_COURS_2_DEMAG  69
#define M_PASSAGE_GAMME_12      70
#define M_PASSAGE_GAMME_34      71
#define M_SAT_CYCLE_1           72
#define M_SAT_CYCLE_2           73
#define M_PRESENCE_COURANT_1      74
#define M_PRESENCE_COURANT_2      75
#define M_STABLITE_MESURE_1       76
#define M_STABLITE_MESURE_2       77
#define M_FIN_ARROSAGE_CYCLE      78
//#define M_                 79

#define M_DCY_MODBUS_RAZ           80
#define M_ACQUIT_DEFAUTS_MODBUS_RAZ   81
#define M_DEMAG_MODBUS_CTRL           82
#define M_BIT_DE_VIE_MODBUS_RAZ       83
#define M_TOR_E4_MEMO             84
#define M_TOR_E3_MEMO             85
#define M_TOR_E2_MEMO             86
#define M_TOR_E1_MEMO             87
#define M_TOR_S1_MODBUS_CTRL_RAZ    88
#define M_TOR_S2_MODBUS_CTRL_RAZ    89
#define M_TOR_S3_MODBUS_CTRL_RAZ    90
#define M_TOR_S4_MODBUS_CTRL_RAZ    91
#define M_ALARME_EXT_MODBUS_CTRL    92
#define M_Desactiv_cycles_MODBUS_CTRL   93
#define M_ACY_MODBUS_RAZ       94
//#define M_                   95

#define M_CONVERSION_0_MODBUS_CTRL  96
#define M_CONVERSION_1_MODBUS_CTRL  97
#define M_NUM_ENTREE_0_MODBUS_CTRL  98
#define M_NUM_ENTREE_1_MODBUS_CTRL  99
//#define M_TM_1_MODBUS_CTRL    100
//#define M_TM_2_MODBUS_CTRL    101
//#define M_!!!!!!!!!!!!        102
//#define M_!!!!!!!!!!!!        103
#define M_FO_1_MODBUS_CTRL      104
#define M_SP_1_MODBUS_CTRL      105
#define M_ET_1_MODBUS_CTRL      106
//#define M_!!!!!!!!!!!!        107
#define M_FO_2_MODBUS_CTRL      108
#define M_SP_2_MODBUS_CTRL      109
#define M_ET_2_MODBUS_CTRL      110
//#define M_!!!!!!!!!!!!        111

#define M_Bspec1_0            112 
#define M_Bspec1_1            113 
#define M_Bspec1_2            114 
#define M_BO_BF               115
#define M_Bspec2_0            116 
#define M_Bspec2_1            117 
#define M_Bspec2_2            118 
#define M_BO_BF2              119 
#define M_Mode0               120 
#define M_Mode1               121 
#define M_MODE_REGLAGE        122 
#define M_MODE_DEFILE         123
#define M_MODE_MAINTENUE      124 
#define M_MODE_INFINI         125 
//#define M_!!!!!!!!!!!!      126 
//#define M_!!!!!!!!!!!!      127 

//#define M_!!!!!!!!!!!!      128 
//#define M_!!!!!!!!!!!!      129 
#define M_CONVER_OCCUP        130 
#define M_CFILLE_COM_ERR      131
//#define M_!!!!!!!!!!!!      132 
//#define M_!!!!!!!!!!!!      133 
//#define M_!!!!!!!!!!!!      134 
//#define M_!!!!!!!!!!!!      135 
#define M_ENTREE_ACTIVE_1     136
#define M_ENTREE_ACTIVE_2     137
#define M_ENTREE_ACTIVE_3     138
#define M_ENTREE_ACTIVE_4     139
#define M_TOR_E4              140
#define M_TOR_E3              141
#define M_TOR_E2              142
#define M_TOR_E1              143

#define M_DCY_MODBUS           160
#define M_ACQUIT_DEFAUTS_MODBUS  161
#define M_DEMAG_MODBUS           162
#define M_BIT_DE_VIE_MODBUS      163
#define M_TOR_E4_MEMO_RAZ        164
#define M_TOR_E3_MEMO_RAZ        165
#define M_TOR_E2_MEMO_RAZ        166
#define M_TOR_E1_MEMO_RAZ        167
#define M_TOR_S1_MODBUS          168
#define M_TOR_S2_MODBUS          169
#define M_TOR_S3_MODBUS          170
#define M_TOR_S4_MODBUS          171
#define M_ALARME_EXT_MODBUS       172
#define M_Desactiv_cycles_MODBUS  173
#define M_ACY_MODBUS             174
#define M_INHIB_Coeff_demag      175

#define M_CONVERSION_0_MODBUS    176
#define M_CONVERSION_1_MODBUS    177
#define M_NUM_ENTREE_0_MODBUS    178
#define M_NUM_ENTREE_1_MODBUS    179
//#define M_TM_1_MODBUS          180
//#define M_TM_2_MODBUS          181
//#define M_                     182
//#define M_                     183
#define M_FO_1_MODBUS            184
#define M_SP_1_MODBUS            185
#define M_ET_1_MODBUS            186
//#define M_                     187
#define M_FO_2_MODBUS            188
#define M_SP_2_MODBUS            189
#define M_ET_2_MODBUS            190
//#define M_                     191

#define M_OPTION_CTRL_TETES_34      192
#define M_SENS_MODE_COMBINE         193 
#define M_OPTION_DEFAUT_THERMIQUE_2 194 
#define M_FIN_ARROSAGE_COMBINE_en_1 195 
#define M_REPOS_4s_GT               196 
#define M_OPTION_DEFAUT_THERMIQUE_1 197 
#define M_OPTION_DOUBLE_AFFICHAGE   198 
#define M_OPTION_CTRL_FORME_ONDE_1  199        
#define M_OPTION_CTRL_FORME_ONDE_2  200 
#define M_OPTION_CTRL_TETES_12    201 
//#define M_                      202 
#define M_PAS_POTARD_TEMPS_05S    203
#define M_MULTI_ET_1         204
#define M_MULTI_ET_2         205
//#define M_                 206
//#define M_                 207

const uint16_t M_FACTEUR_THERMIQUE_C[3]    ={0,M_FACTEUR_THERMIQUE_1,M_FACTEUR_THERMIQUE_2};   
const uint16_t M_MESURE_CRETE_C[4]      ={0,M_MESURE_CRETE_1,M_MESURE_CRETE_2,M_MESURE_CRETE_3};
const uint16_t M_MESURE_EFF_C[4]        ={0,M_MESURE_EFF_1,M_MESURE_EFF_2,M_MESURE_EFF_3};
const uint16_t M_type_boucle[4]       ={M_BO_BF,M_BO_BF,M_BO_BF2,M_BO_BF2};

const uint16_t M_TOR_E[4]       ={M_TOR_E1,M_TOR_E2,M_TOR_E3,M_TOR_E4};

// Adresse P

#define P_SWAP_FO_1             49
#define P_SWAP_FO_2             50
#define P_Regul1_C1             51
#define P_Regul1_C2             52
#define P_Regul2_C1             53
#define P_Regul2_C2             54
#define P_Regul3_C1             55
#define P_Regul3_C2             56
#define P_Mes_Sup80pTubeCone_C1     57
#define P_Mes_Sup80pTubeCone_C2     58
#define P_FIN_TPS_MAG_C2        59
#define P_FIN_TPS_MAG_C1        60
#define P_ENABLE_Affichage_1    61
#define P_ENABLE_Affichage_2    62
#define P_DEMAG_EN_COURS        63  

#define P_DCY                   64
#define P_ACQUIT_DEFAUTS        65
#define P_DEMAG                 66
#define P_ACY                   67
//#define P_                    68
#define P_FO_1_memo             69
#define P_FO_2_memo             70
#define P_FOSP_1_memo           71
#define P_FOSP_2_memo           72
#define P_Depassement_Seuil_Fth_1    73
#define P_Depassement_Seuil_Fth_2    74
#define P_DEPASS_SEUIL_TEMPERATURE_0 75
#define P_DEPASS_SEUIL_TEMPERATURE_1 76
#define P_DEPASS_SEUIL_TEMPERATURE_2 77
#define P_DEPASS_SEUIL_TEMPERATURE_3 78
//#define P_                 79

#define P_OFFSET_3_4              80
#define P_OFFSET_1_2              81
#define P_CFILLE_OCCUP            82
#define P_CONVER_COM_ERR          83
#define P_ACTIVATION_ENTREES_SUP  84
//#define P_!!!!!!!!!!!!          85
//#define P_!!!!!!!!!!!!          86
//#define P_!!!!!!!!!!!!          87    
#define P_SORTIE_ACTIVE_1         88
#define P_SORTIE_ACTIVE_2         89
#define P_SORTIE_ACTIVE_3         90
#define P_SORTIE_ACTIVE_4         91
#define P_TOR_S1               92
#define P_TOR_S2               93
#define P_TOR_S3               94
#define P_TOR_S4               95  

#define P_CONVERSION_0         96
#define P_CONVERSION_1         97
#define P_NUM_ENTREE_0         98
#define P_NUM_ENTREE_1         99
//#define P_TM_1              100
//#define P_TM_2              101
//#define P_!!!!!!!!!!!!      102
//#define P_!!!!!!!!!!!!      103     
#define P_FO_1                104
#define P_SP_1                105 
#define P_ET_1                106
//#define P_!!!!!!!!!!!!      107
#define P_FO_2                108
#define P_SP_2                109 
#define P_ET_2                110
//#define P_!!!!!!!!!!!!      111

#define P_SEUIL_CAPTEUR_TEMPERATURE_0 112
#define P_SEUIL_CAPTEUR_TEMPERATURE_1 113
#define P_SEUIL_CAPTEUR_TEMPERATURE_2 114
#define P_SEUIL_CAPTEUR_TEMPERATURE_3 115

#define P_N_VOIE_FO_B0_C1         116
#define P_N_VOIE_FO_B1_C1         117
#define P_N_VOIE_FO_B2_C1         144

#define P_N_VOIE_FO_B0_C2         118
#define P_N_VOIE_FO_B1_C2         119 
#define P_N_VOIE_FO_B2_C2         145 


#define P_N_VOIE_FO_B0_C3         128
#define P_N_VOIE_FO_B1_C3         129 
#define P_N_VOIE_FO_B2_C3         146 

#define P_CPT_SWAP_FO_B0_C1       120
#define P_CPT_SWAP_FO_B1_C1       121
#define P_CPT_SWAP_FO_B0_C2       122
#define P_CPT_SWAP_FO_B1_C2       123
#define P_ACY_MEMO                124
#define P_FIN_STAB_MAG_C1         125
#define P_FIN_STAB_MAG_C2         126


const uint16_t P_N_VOIE_FO_B0_C[4]        = {P_N_VOIE_FO_B0_C1,P_N_VOIE_FO_B0_C1,P_N_VOIE_FO_B0_C2,P_N_VOIE_FO_B0_C3};
const uint16_t P_N_VOIE_FO_B1_C[4]        = {P_N_VOIE_FO_B1_C1,P_N_VOIE_FO_B1_C1,P_N_VOIE_FO_B1_C2,P_N_VOIE_FO_B1_C3};

// En cours de test 
const uint16_t P_N_VOIE_FO_B2_C[4]        = {P_N_VOIE_FO_B2_C1,P_N_VOIE_FO_B2_C1,P_N_VOIE_FO_B2_C2,P_N_VOIE_FO_B2_C3};

//                                  voies ={0,1,2,3,4,7,8,5,6,9}
const uint16_t P_N_VOIE_FO_B0_V[10]        ={0,0,1,0,1,0,0,0,1,0};
const uint16_t P_N_VOIE_FO_B1_V[10]        ={0,0,0,1,1,0,1,0,0,0};

// En cours de test 
const uint16_t P_N_VOIE_FO_B2_V[10]        ={0,0,0,0,0,0,0,1,1,1};


//const uint16_t P_ENABLE_Affichage_C[3]    ={ENABLE_Affichage_1,ENABLE_Affichage_1,ENABLE_Affichage_2};
const uint16_t P_FO_C[3]                  ={P_FO_1,P_FO_1,P_FO_2};
const uint16_t P_DEPASS_SEUIL_TEMPERATURE[4]  ={P_DEPASS_SEUIL_TEMPERATURE_0,P_DEPASS_SEUIL_TEMPERATURE_1,P_DEPASS_SEUIL_TEMPERATURE_2,P_DEPASS_SEUIL_TEMPERATURE_3};
const uint16_t P_SEUIL_CAPTEUR_TEMPERATURE[4] ={P_SEUIL_CAPTEUR_TEMPERATURE_0,P_SEUIL_CAPTEUR_TEMPERATURE_1,P_SEUIL_CAPTEUR_TEMPERATURE_2,P_SEUIL_CAPTEUR_TEMPERATURE_3};
