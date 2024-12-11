#include <stdio.h>
#include <iostream>

#define SIZE (100)
#define HSIZE (10)
#define NROW (100)
#define NCOL (100)
#define NRH (10)
#define NCH (10)
#define BSIZE (64)
#define BX (8)
#define BY (8)

void cpu_convo2d(float *A, float *B, float *C, int n, int p) {
    for (int i = 0; i < n; i++) {
        float s = 0.0;
        for (j = max(0, i - p + 1); j <= i; j++) {
            s += x[j] * h[i - j];
        }
        y[i] = s;
    }
}

int main(int argc, char *argv[]) {
    return 0;
}
