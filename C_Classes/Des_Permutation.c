//
// Created by root on 15/04/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Head_Classes/Des_Permutation.h"
#include "../Head_Classes/Des_FonctionF.h"




//cette fonction nous permet la permutation du nombre de tableau de permutation équivalent à la taille du bit en sortie et retourne le resultat du permutation final
long permutation(long message, int table_permutation[] ,int tailleBits_entre, int tailleBits_sortie)
{
    long tmp;

    long permut = 0x0;
    long bit_position = 0x1;

    for (int i=0;i<tailleBits_sortie;i++)
    {
        tmp = et_binaire(message, dec_gauche(bit_position,tailleBits_entre - table_permutation[i]));//Recuperation du bit

        if (tmp != 0)
        {
            tmp = bit_position;
            tmp = dec_gauche(tmp,(tailleBits_sortie - i - 1));
        }


        permut = concat(permut,tmp);
    }

    return permut;
}