cmake_minimum_required(VERSION 3.16)
project(DES_Application C)

set(CMAKE_C_STANDARD 99)

add_executable(DES_Application main.c C_Classes/Des_Permutation.c Head_Classes/Des_TablesPermut.h Head_Classes/Des_Permutation.h C_Classes/Des_FonctionF.c Head_Classes/Des_FonctionF.h C_Classes/Des_Algorithme.c Head_Classes/Des_Algorithme.h C_Classes/Des_keyShedule.c Head_Classes/Des_keyShedule.h C_Classes/Des_K16.c Head_Classes/Des_K16.h Head_Classes/Des_K64.h C_Classes/Des_K64.c)