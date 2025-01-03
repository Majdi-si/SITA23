#include <stdio.h>

void sum_m(int list[], int length, int *max_sum, int *max_i, int *max_j) {
    *max_i = 0;
    *max_j = 0;
    *max_sum = 0;

    for (int i = 0; i < length; i++) {
        int sum = 0;
        for (int j = i; j < length; j++) {
            sum += list[j];
            if (sum > *max_sum) {
                *max_sum = sum;
                *max_i = i;
                *max_j = j;
            }
        }
    }
}

int main() {
    int list[] = {1, -2, 1, 2, -1, 3, -2, 1};
    int length = sizeof(list) / sizeof(list[0]);
    int max_sum, max_i, max_j;

    sum_m(list, length, &max_sum, &max_i, &max_j);

    printf("Max sum: %d, from index %d to %d\n", max_sum, max_i, max_j);

    return 0;
}