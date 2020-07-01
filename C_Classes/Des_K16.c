//
// Created by root on 18/04/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Head_Classes/Des_Permutation.h"
#include "../Head_Classes/Des_FonctionF.h"
#include "../Head_Classes/Des_TablesPermut.h"
#include "../Head_Classes/Des_Algorithme.h"





//Récuperer la clé K16 48 bits
long recupSolution(int cle[][6][64],int solPossibles[][6],int NUM_SBOX,long K16)
{
    int test = 0;
    int final_solution;

    long elu = (long) cle[NUM_SBOX][0][test];

    for (int nbr_Faux = 1; nbr_Faux < 6; nbr_Faux++)
    {
        for (final_solution = 0;final_solution<solPossibles[NUM_SBOX][nbr_Faux];final_solution++)
        {
            if (elu == cle[NUM_SBOX][nbr_Faux][final_solution])
            {
                break;
            }
        }

        if(final_solution == solPossibles[NUM_SBOX][nbr_Faux])
        {
            if(test+1 >= solPossibles[NUM_SBOX][0])
            {
                printf("\nProblème Sbox numéro %d,chiffré faux %d\n",NUM_SBOX,nbr_Faux);
                break;
            }
            nbr_Faux = 1;
            ++test;
            elu = (long) cle[NUM_SBOX][0][test];
        }
    }
    printf("\nPour la SBOX %d on trouve : %lX\n",NUM_SBOX+1,elu);
    printf("\nConcatener la valeur trouve %lX à K16\n",elu);
    K16 = dec_gauche(K16,6);
    K16 = concat(K16,elu);
    printf("\nK16 courant = %lX\n",K16);

    return K16;
}
//Permet d'afficher le solution de la cle k16 au niveau du Sbox
void affiche_sol(int NUM_SBOX,int solPossibles[][6],int cle[][6][64])
{

    printf("\nSbox %d \n\n", NUM_SBOX + 1);
    for (int nbr_faux=0;nbr_faux<6;nbr_faux++)
    {
        printf("Chiffré Faux %d : %d clés K16 ->	", nbr_faux+1, solPossibles[NUM_SBOX][nbr_faux]);

        for (int i =0;i<solPossibles[NUM_SBOX][nbr_faux];i++)
        {
            printf("%X ", cle[NUM_SBOX][nbr_faux][i]);
        }
        printf("\n");
    }

}

//Cette fonction permet de retrouver la clé K16 de taille 48 bits
long trouverK16_48b(long msg_EncJuste, long msg_EncFaux[])
{
    long K16 = 0;
    long msg_Dec_EncJuste;
    long msg_Dec_EncFaux;
    long check;
    long entree_SBOX,entree_SBOXf;
    long EXP_R15, EXP_R15f;
    long L16,R16,R15,L16f,R16f,R15f;


    int cle[8][6][64] = {{{0}}};
    int solPossibles[8][6] = {{0}};

    int nbr_faux;

    int check_4bits;
    int SBOX_4bits;
    int ligne,colonne;
    int ligne_f,colonne_f;
    int NUM_SBOX ;
    int RE_k16;


    msg_Dec_EncJuste = permutation(msg_EncJuste, IP, 64, 64);



    L16 = decoupage_msgL(msg_Dec_EncJuste,0xFFFFFFFF);
    R16 = decoupage_msgR(msg_Dec_EncJuste,0xFFFFFFFF);


    R15 = R16;
    //Recherche exhaustive
    for(NUM_SBOX=0;NUM_SBOX<8;NUM_SBOX++)
    {
        for(nbr_faux=0;nbr_faux<6;nbr_faux++)
        {
            msg_Dec_EncFaux = permutation(msg_EncFaux[position_bitfaux[NUM_SBOX][nbr_faux]], IP, 64, 64);



            L16f = decoupage_msgL(msg_Dec_EncFaux,0xFFFFFFFF);
            R16f = decoupage_msgR(msg_Dec_EncFaux,0xFFFFFFFF);


            R15f=R16f;

            check = permutation(xor(L16,L16f),inver_P,32,32);

            EXP_R15=permutation(R15,E,32,48);
            EXP_R15f=permutation(R15f,E,32,48);

            for (RE_k16=0;RE_k16<64;RE_k16++)
            {
                entree_SBOX = xor(dec_droite(decoupe_6bits(EXP_R15,NUM_SBOX),trouver_SBOX_6bits(NUM_SBOX)),RE_k16);
                entree_SBOXf = xor(dec_droite(decoupe_6bits(EXP_R15f,NUM_SBOX),trouver_SBOX_6bits(NUM_SBOX)),RE_k16);

                ligne = calcul_lignes_SBOX(entree_SBOX);
                colonne = calcul_col_SBOX(entree_SBOX);

                ligne_f = calcul_lignes_SBOX(entree_SBOXf);
                colonne_f = calcul_col_SBOX(entree_SBOXf);

                check_4bits =dec_droite(decoupe_4bits(check,NUM_SBOX),trouver_SBOX_4bits(NUM_SBOX));
                SBOX_4bits = xor(Sbox[NUM_SBOX][ligne][colonne],Sbox[NUM_SBOX][ligne_f][colonne_f]);

                if(check_4bits == SBOX_4bits)
                {
                    cle[NUM_SBOX][nbr_faux][solPossibles[NUM_SBOX][nbr_faux]] = RE_k16;
                    ++solPossibles[NUM_SBOX][nbr_faux];
                }
            }
        }

        affiche_sol(NUM_SBOX,solPossibles,cle);//Affichage Possibilités par SBOX

        K16=recupSolution(cle,solPossibles,NUM_SBOX,K16);
        printf("\n------------------------------------------------- \n");
    }



    return K16;
}


//Cette fonction permet de retrouver les bits perdus de la clé K
long bitsPerdus(long mask)
{
    long recup = 0;
    long bits_perdu[] = {14,15,19,20,51,54,58,60};

    for(int i = 0;i<8;i++)
    {
        recup = concat(recup,dec_gauche(et_binaire(dec_droite(mask,i),1),(64 - bits_perdu[i])));
    }

    return recup;
}


//Cette fonction permet de trouver la clé K16 de 56 bits
long trouverK16_56b(long msg_Clair,long msg_EncJuste,long K16_48b)
{
    long K48_56;
    long K56_64;

    long mask = 0;
    long RE_K ;//Recherche exhaustive pour trouver les 8bits faux

    K48_56 = permutation(K16_48b,inver_PC2,48,56);

    K56_64 = permutation(K48_56,inver_PC1,56,64);

    RE_K = K56_64;

    while(mask<256 && msg_EncJuste != DES(msg_Clair,RE_K) )
    {
        RE_K = concat(K56_64,bitsPerdus(mask));//2^8 =256 possibilités
        mask++;
    }

    if (mask == 256)
    {
        printf("\nErreur K 56bits\n");
    }

    return RE_K;

}


