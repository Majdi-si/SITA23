#include <stdio.h>
#include <stdlib.h>

#include "ctp6_1.h"

extern euro mon_compte_international;
// extern car il s'agit de la variable déclarée dans le fichier "ctp6_1.c"

int main()
{
jeconsomme(mon_compte_international);
printf(" -1- \n");
jeconsomme(mon_compte_secret);

jeconsommelocal(mon_compte_international);
jeconsommelocal(mon_compte_secret);

jeteste();

return 0;
}

