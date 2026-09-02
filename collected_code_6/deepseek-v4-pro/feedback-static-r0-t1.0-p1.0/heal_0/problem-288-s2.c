#include <stdio.h>
#include <stdlib.h>

int count_self_inverse_mod_p(const int *arr, int n, int p, int *err) {
    if (arr == NULL || p <= 1) {
        if (err != NULL) {
            *err = 1;
        }
        return 0;
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        int a = arr[i] % p;
        if (a < 0) {
            a += p;
        }
        if (a == 0) {
            continue;
        }
        if ((1LL * a * a) % p == 1) {
            count++;
        }
    }

    if (err != NULL) {
        *err = 0;
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 11;
    int err = 0;

    int result = count_self_inverse_mod_p(arr, n, p, &err);
    if (err != 0) {
        fprintf(stderr, "Error: invalid input parameters\n");
        return EXIT_FAILURE;
    }

    printf("Count of self-inverse elements modulo %d: %d\n", p, result);
    return EXIT_SUCCESS;
}