//
// Created by root on 17/04/2020.
//

#ifndef DES_APPLICATION_DES_FONCTIONF_H
#define DES_APPLICATION_DES_FONCTIONF_H



long et_binaire(long a, long b);

long dec_droite(long a, int b);

long dec_gauche(long a, int b);

long concat(long a,long b);

long xor(long a,long b);

long decoupage_msgR(long msg,long mask);

long decoupage_msgL(long msg,long mask);

int calcul_col_SBOX(int bloc6bits);

int calcul_lignes_SBOX(int bloc6bits);

int trouver_SBOX_4bits(int NUM_SBOX);

int trouver_SBOX_6bits(int SBOX);

long decoupe_4bits(long check,int NUM_SBOX);

long decoupe_6bits(long expansion,int SBOX);

long Fonction_F(long R, long Ki);

#endif //DES_APPLICATION_DES_FONCTIONF_H
