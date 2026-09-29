#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void power_of_elements(const int *list, int list_size, int n, double *result) {
    for (int i = 0; i < list_size; i++) {
        result[i] = pow(list[i], n);
    }
}

int main(void) {
    int list[] = {2, 3, 4, 5, 6};
    int list_size = sizeof(list) / sizeof(list[0]);
    int n = 3;

    double *result = malloc((size_t)list_size * sizeof(double));
    if (result == NULL) {
        return 1;
    }

    power_of_elements(list, list_size, n, result);

    for (int i = 0; i < list_size; i++) {
        printf("%d^%d = %.0f\n", list[i], n, result[i]);
    }

    free(result);
    return 0;
}