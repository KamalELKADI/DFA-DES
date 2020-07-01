#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Head_Classes/Des_K16.h"
#include "Head_Classes/Des_K64.h"
#include "Head_Classes/Des_Algorithme.h"


int main()
{
    long message_clair = 0x62F70402DF92B3B6;
    long message_EncryptionJuste = 0x3535337AC6E41119;
    long message_EncryptionFaux[] = {
            0x3720337EC6E5110D,
            0x3527333AC6E41119,
            0x3525313EC6E51119,
            0x35653738D6E51119,
            0x3575333ED4E41119,
            0x3475337AD6E61119,
            0x3575377AC6E41319,
            0x3435337BD6F0111B,
            0x3D75377BC6F41119,
            0x353D337B86F41119,
            0x35353B7B86E01119,
            0x7535237386B01118,
            0x3535337BCEB41118,
            0x3535237AC6AC1118,
            0x7535337AC6E41918,
            0x7535237AC6A41051,
            0x1535237AC6A40159,
            0x3515337AC2E41019,
            0x3535137AC6E41059,
            0x3535725AC2E41159,
            0x3135327AE2E40159,
            0x2535727AC6C41119,
            0x2135327AC6E43119,
            0x2135726AC6E41539,
            0xA535326AC6E45119,
            0x35B5336AC6E45519,
            0x3535B36AC7E41119,
            0x353133FAC6E45509,
            0x3531337A47E4150D,
            0x3531337AC664111D,
            0x3535337AC6E4910D,
            0x3520337EC6E4119D
    };

    long verification;
    long K16_48bits;
    long K_64bits;

    //Exemple d'exécution d'un chiffrement DES
    printf("\n############################################\n");
    printf("\n## Exemple exécution DES ##\n");

    printf("Clair = %lx | Chiffré Juste = %lx \n", message_clair, message_EncryptionJuste);


    printf("\n############################################\n\n");
    printf("\n## Recherche de la clé K16 48 bits ##\n");
    K16_48bits = trouverK16_48b(message_EncryptionJuste,message_EncryptionFaux);

    printf("\nla clé finale de K16_48bits est  = %lX \n",K16_48bits);




    K_64bits=trouver_K64(message_clair,message_EncryptionJuste,K16_48bits);

    printf("\nla clé K 64bits = %lX\n", K_64bits);


    printf("\n############################################\n\n");
    printf("## Vérification de la clé trouvé K64 bits ##\n\n");
    verification=DES(message_clair,K_64bits);

    printf("Clé trouvé K = %lX \n",K_64bits);
    printf("Message Clair = %lX \n",message_clair);
    printf("Message Chiffré Juste = %lX \n",message_EncryptionJuste);
    printf("Chiffré trouvé avec Algo DES et K64 = %lX \n",verification);

    return 0;
}

