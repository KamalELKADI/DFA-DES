//
// Created by root on 17/04/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Head_Classes/Des_Permutation.h"
#include "../Head_Classes/Des_FonctionF.h"
#include "../Head_Classes/Des_TablesPermut.h"


//Cette fonction permet le Et binaire
long et_binaire(long a, long b)
{
    return (a & b);
}


//cette fonction permet le décalage à droite
long dec_droite(long a, int b)
{
    return (a >> b);
}



//cette fonction permet le décalage à gauche
long dec_gauche(long a, int b)
{
    return (a << b);
}

//cette fonction permet la concatenation entre 2 long
long concat(long a,long b)
{
    return (a | b);
}


//cette fonction fait le XOR
long xor(long a,long b)
{
    return (a ^ b);
}



//cette fonction stock la partie L du message
long decoupage_msgL(long msg,long mask)
{
    return (msg >> 32) & mask;
}


//cette fonction stock la partie R du message
long decoupage_msgR(long msg,long mask)
{
    return msg & mask;
}


//cette fonction calcule les colonnes des Sbox
int calcul_col_SBOX(int bloc6bits)
{
    return ((bloc6bits & 0x1E) >> 1);
}


 //cette fonction calcule les lignes des Sbox
int calcul_lignes_SBOX(int bloc6bits)
{
    return (2 * ((bloc6bits & 0x20) >> 5) + (bloc6bits & 0x1));
}

long decoupe_4bits(long check,int NUM_SBOX)
{
    return check & mask4[NUM_SBOX];
}

 //cette fonction decoupe l'expansion en blocs de 6 bits pour chaque Sbox
long decoupe_6bits(long expansion,int NUM_SBOX)
{
    return expansion & mask6[NUM_SBOX];
}

 //cette fonction trouve la bonne sbox d'ou se trouve les 48 bits de sortie
int trouver_SBOX_4bits(int NUM_SBOX)
{
    return (7 - NUM_SBOX) * 4;
}


 //elle permet de trouver la bonne sbox d'ou il est injecté les 6 bits
int trouver_SBOX_6bits(int NUM_SBOX)
{
    return (7 - NUM_SBOX) * 6;
}



//Cette une fonction qui applique la fonction F du DES
long Fonction_F(long R, long sous_cle)
{
    long Enter_Sbox;
    long Sortie_Sbox=0x0;
    long expansion;
    long ligne,colonne;
    long bloc_6bits;// Decoupage 6bits pour entréee des SBOX

    expansion = permutation(R,E,32,48);

    Enter_Sbox = xor(expansion,sous_cle);

    for (int i=0;i<8;i++)
    {
        bloc_6bits = dec_droite(Enter_Sbox,et_binaire((48 - 6 - i*6),0x3F));

        ligne = calcul_lignes_SBOX(bloc_6bits);
        colonne = calcul_col_SBOX(bloc_6bits);

        Sortie_Sbox = concat(Sortie_Sbox,dec_gauche(Sbox[i][ligne][colonne],(32 - 4 - i*4)));
    }

    return permutation(Sortie_Sbox,P,32,32);
}


