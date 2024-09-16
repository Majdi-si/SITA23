#include <stdio.h>
#include <math.h>

double second_degre (float a, float b, float c){
    float disc;
    float x1;
    float x2;
    disc = pow(b,2) - 4*a*c;
    if (a == 0 && b == 0 && c == 0){
        printf("Tout réel est solution\n");
    }
    else if (a == 0 && b ==0){
        printf("Impossible car a et b sont nuls\n");
    }
    else if (a == 0 && disc >=0){
        return -c/b;
    }
    else if (b == 0 && disc >=0){
        x1 = -sqrt(disc)/(2*a);
        x2 = sqrt(disc)/(2*a);
        return (x1, x2) ;
    }
    else if (c == 0 && disc >=0){
        return -b/a;
    }
    else if (disc < 0){
        printf("Pas de solutions réelles\n");
    }
    else if (disc == 0){
        return -b/2*a;
    }
    else {
        x1 = -b-sqrt(disc)/(2*a);
        x2 = -b + sqrt(disc)/(2*a);
        return (x1, x2);
    }

};

int main()
{
    printf("%lf \n", second_degre(3,-1,-10));

    return 0 ;
}
