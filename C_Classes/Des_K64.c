//
// Created by root on 20/04/2020.
//

#include <stdio.h>

#include "../Head_Classes/Des_K16.h"
#include "../Head_Classes/Des_K64.h"
#include "../Head_Classes/Des_FonctionF.h"


//retrouver les bits de parité
long recup_bits_de_Parite(long K56b)
{
    long recup = K56b;
    long test, parite;

    for(int i=0;i<8;i++)
    {
        parite = 0;

        for(int j=0;j<8;j++)
        {
            if(j!=7)
            {
                test = dec_gauche(1,( ((7 - i) * 8) + (7 - j) ));
                test = et_binaire(K56b,test);

                if(test)
                {
                    parite = xor(parite,1);
                }
                else
                {
                    parite = xor(parite,0);
                }
            }
            else
            {
                test = !parite;
                recup = concat(recup,dec_gauche(test,((7 - i) * 8)));
            }
        }
    }
    return recup;
}

//permet de retrouver clé K 64 bits
long trouver_K64(long msg_Clair,long msg_EncJuste,long K16_56b)
{
    printf("\n############################################\n\n");
    printf("## Recherche de la clé K16 56bits##\n\n");
    long K56b = trouverK16_56b(msg_Clair, msg_EncJuste, K16_56b);
    printf("\la clé K 56bits = %lX\n", K56b);


    printf("\n############################################\n\n");
    printf("## Recherche de la clé K 64bits ##\n");
    long K64b = recup_bits_de_Parite(K56b);

    return K64b;
}

