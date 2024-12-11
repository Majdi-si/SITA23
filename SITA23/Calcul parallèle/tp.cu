#include <stdio.h>
#include <cuda.h>

// Kernel pour le produit de convolution 1D
__global__ void conv1D(int n, float *x, int p, float *h, float *y) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // Calcul de l'index global
    if (idx < n) {
        float sum = 0.0;
        for (int k = max(0, idx - p + 1); k <= idx; k++) {
            sum += x[k] * h[idx - k];
        }
        y[idx] = sum; // Stocke le résultat dans le vecteur de sortie
    }
}

// Kernel pour le produit de convolution 2D
__global__ void conv2D(int m, int n, float *x, int p, int q, float *h, float *y) {
    int i = blockIdx.y * blockDim.y + threadIdx.y; // Index ligne
    int j = blockIdx.x * blockDim.x + threadIdx.x; // Index colonne

    if (i < m && j < n) {
        float sum = 0.0;
        for (int k = max(0, i - p + 1); k <= i; k++) {
            for (int l = max(0, j - q + 1); l <= j; l++) {
                sum += x[k * n + l] * h[(i - k) * q + (j - l)];
            }
        }
        y[i * n + j] = sum; // Stocke le résultat dans la matrice de sortie
    }
}

int main() {
    // Dimensions du problème pour l'exemple
    const int n = 10; // Taille du vecteur 1D
    const int m = 4, nc = 4; // Dimensions de la matrice 2D
    const int p = 3, q = 3; // Dimensions des filtres

    // Allocation mémoire sur l'hôte
    float h_x1D[n] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Vecteur d'entrée
    float h_h1D[p] = {1, 0, -1}; // Filtre 1D
    float h_y1D[n] = {0}; // Résultat 1D

    float h_x2D[m * nc] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; // Matrice d'entrée
    float h_h2D[p * q] = {0, 1, 0, 1, -4, 1, 0, 1, 0}; // Filtre 2D
    float h_y2D[m * nc] = {0}; // Résultat 2D

    // Allocation mémoire sur le device
    float *d_x1D, *d_h1D, *d_y1D;
    float *d_x2D, *d_h2D, *d_y2D;

    cudaMalloc(&d_x1D, n * sizeof(float));
    cudaMalloc(&d_h1D, p * sizeof(float));
    cudaMalloc(&d_y1D, n * sizeof(float));

    cudaMalloc(&d_x2D, m * nc * sizeof(float));
    cudaMalloc(&d_h2D, p * q * sizeof(float));
    cudaMalloc(&d_y2D, m * nc * sizeof(float));

    // Copie des données sur le device
    cudaMemcpy(d_x1D, h_x1D, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_h1D, h_h1D, p * sizeof(float), cudaMemcpyHostToDevice);

    cudaMemcpy(d_x2D, h_x2D, m * nc * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_h2D, h_h2D, p * q * sizeof(float), cudaMemcpyHostToDevice);

    // Lancement des kernels
    dim3 block1D(256);
    dim3 grid1D((n + block1D.x - 1) / block1D.x);

    conv1D<<<grid1D, block1D>>>(n, d_x1D, p, d_h1D, d_y1D);

    dim3 block2D(16, 16);
    dim3 grid2D((nc + block2D.x - 1) / block2D.x, (m + block2D.y - 1) / block2D.y);

    conv2D<<<grid2D, block2D>>>(m, nc, d_x2D, p, q, d_h2D, d_y2D);

    // Copie des résultats vers l'hôte
    cudaMemcpy(h_y1D, d_y1D, n * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(h_y2D, d_y2D, m * nc * sizeof(float), cudaMemcpyDeviceToHost);

    // Affichage des résultats
    printf("Résultat de la convolution 1D :\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f ", h_y1D[i]);
    }
    printf("\n\n");

    printf("Résultat de la convolution 2D :\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%.2f ", h_y2D[i * nc + j]);
        }
        printf("\n");
    }

    // Libération de la mémoire
    cudaFree(d_x1D);
    cudaFree(d_h1D);
    cudaFree(d_y1D);

    cudaFree(d_x2D);
    cudaFree(d_h2D);
    cudaFree(d_y2D);

    return 0;
}
