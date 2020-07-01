//
// Created by root on 18/04/2020.
//

#ifndef DES_APPLICATION_DES_K16_H
#define DES_APPLICATION_DES_K16_H

long bitsPerdus(long mask);

long trouverK16_56b(long msg_Clair,long msg_EncJuste,long K16_48b);

long recupSolution(int cle[][6][64],int solPossibles[][6],int NUM_SBOX,long K16);

long trouverK16_48b(long msg_EncJuste, long msg_EncFaux[]);

#endif //DES_APPLICATION_DES_K16_H
