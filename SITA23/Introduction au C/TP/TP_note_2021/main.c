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

    chargerPilotes(&nbp,&pilotes, "fichier_pilotes.txt");

    afficherPilotes(nbp,pilotes);

    chargerCourses(&nbc, &courses,"fichier_courses.txt");
    afficherCourses(nbc,courses);

    initPointsClassement(&tabclas);

    calculerPointsPilotes(nbp,pilotes,tabclas, nbc,courses);

    afficherPilotes(nbp,pilotes);

    sauverPilotes(nbp,pilotes,"pilotesresultats.txt");
    liberer(&nbp,&pilotes, &nbc, &courses, &tabclas);
    return 0;
}