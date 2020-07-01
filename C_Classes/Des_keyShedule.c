//
// Created by root on 17/04/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Head_Classes/Des_Permutation.h"
#include "../Head_Classes/Des_TablesPermut.h"
#include "../Head_Classes/Des_keyShedule.h"
#include "../Head_Classes/Des_FonctionF.h"



//Cette fonction nous permet la rotation gauche de chaque moitié de K56 bits et qui retourne un msg crypté
long Rotation_Gauche(long K56)
{
    long C28,D28;
    long test;

    C28 = dec_droite(et_binaire(K56,0xFFFFFFF0000000),28);
    D28 = et_binaire(K56,0xFFFFFFF);

    test = dec_droite(C28,27);
    C28 = dec_gauche(C28,1);
    C28 = et_binaire(C28,0xFFFFFFF);
    C28 = concat(C28,test);

    test = dec_droite(D28,27);
    D28 = dec_gauche(D28,1);
    D28 = et_binaire(D28,0xFFFFFFF);
    D28 = concat(D28,test);

    C28 = dec_gauche(C28,28);

    return et_binaire(concat(C28,D28),0xFFFFFFFFFFFFFF);
}


//Cette fonction calcule chaque sous clé
void DES_sousCle(long sous_cles[],long K64)
{

    int permutation_keysh[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

    long K56 = permutation(K64,PC1,64,56);

    for(int i=0;i<16;i++)
    {
        if (permutation_keysh[i] == 1)
        {
            K56 = Rotation_Gauche(K56);
        }
        else
        {
            K56 = Rotation_Gauche(Rotation_Gauche(K56));
        }

        sous_cles[i] = permutation(K56,PC2,56,48);
    }
}


