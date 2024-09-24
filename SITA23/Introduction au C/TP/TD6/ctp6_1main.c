#include <stdio.h>
#include <stdlib.h>

#include "ctp6_1.h"

extern euro mon_compte_international;
// extern car il s'agit de la variable déclarée dans le fichier "ctp6_1.c"

int main()
{
jeconsomme(mon_compte_international);
printf(" -1- \n");
// jeconsomme(mon_compte_secret);

// jeconsommelocal(mon_compte_international);
// jeconsommelocal(mon_compte_secret);

jeteste();

return 0;
}


//1. Pourquoi dans le main ne pouvez‐vous pas accéder à « mon_compte_secret » ?
// On ne peut pas accéder à "mon_compte_secret" car je ne l'ai pas importé

// Pourquoi dans le main ne pouvez‐vous pas accéder à la fonction « je consommelocal » ?
// On ne peut pas accéder à "jeconsommelocal" car elle est déclarée en static dans le fichier "ctp6_1.c"

//Pourquoi la fonction « jeteste » y a accès ?
// La fonction "jeteste" a accès car elle est déclarée dans le fichier "ctp6_1.c" et que j'ai importé le fichier "ctp6_1.h" dans le main