#include <stdio.h>
#include "ctp6_1.h"

// on va déclarer certaines variables globales :

euro mon_compte_international=1000;
static euro mon_compte_secret=10000;

/***********************/
void jeconsomme(euro e)
{
    printf("\n je consomme %d euros.\n",e);
}

/************************/
static void jeconsommelocal(euro e)
{
    printf("\n je consomme localement %d euros.\n",e);
}

/**********************/
void jeteste()
{
    jeconsomme(mon_compte_international);
    jeconsomme(mon_compte_secret);
    jeconsommelocal(mon_compte_international);
    jeconsommelocal(mon_compte_secret);

}
