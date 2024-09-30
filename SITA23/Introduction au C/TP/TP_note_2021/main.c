#include <stdio.h>
#include <stdlib.h>
#include "gp.h"

int main()
{
    Pilote *pilotes=NULL;
    int nbp=0;

    int *tabclas=NULL;

    Course *courses=NULL;
    int nbc=0;

    chargerPilotes(&nbp,&pilotes, "pilotes.txt");
    afficherPilotes(nbp,pilotes);

    chargerCourses(&nbc, &courses,"courses.txt");
    afficherCourses(nbc,courses);

    initPointsClassement(&tabclas);

    calculerPointsPilotes(nbp,pilotes,tabclas, nbc,courses);

    sauverPilotes(nbp,pilotes,"pilotesresultats.txt");
    liberer(&nbp,&pilotes, &nbc, &courses, &tabclas);
    return 0;
}