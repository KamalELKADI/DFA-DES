//
// Created by root on 16/04/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Head_Classes/Des_Permutation.h"
#include "../Head_Classes/Des_Algorithme.h"
#include "../Head_Classes/Des_TablesPermut.h"
#include "../Head_Classes/Des_FonctionF.h"
#include "../Head_Classes/Des_keyShedule.h"


//cette fonction permer d'éxecuter l'algorithme DES et retourne un msg crypté
long DES(long message_clair,long K64)
{
    long sous_cles[16]={0};
    long L,R;
    long Li,Ri;

    DES_sousCle(sous_cles,K64);

    L = decoupage_msgL(permutation(message_clair,IP,64,64),0xFFFFFFFF);
    R = decoupage_msgR(permutation(message_clair,IP,64,64),0xFFFFFFFF);

    for (int i=0;i<16;i++)
    {
        Li = R;
        Ri = xor(L,Fonction_F(R,sous_cles[i]));

        L = Li;
        R = Ri;

    }

    return permutation(concat(dec_gauche(R,32),L),inver_IP,64,64);

}


