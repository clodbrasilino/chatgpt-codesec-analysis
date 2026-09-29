#include <stdio.h>
#include <stdlib.h>

int count_0th_and_nth_bits(const int *arr, size_t size, unsigned int n) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if ((arr[i] & 1) && (arr[i] & (1 << n))) {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <n> <val1> <val2> ...\n", argv[0]);
        return 1;
    }

    unsigned long n_val = strtoul(argv[1], NULL, 10);
    if (n_val >= sizeof(int) * 8) {
        fprintf(stderr, "Error: n exceeds bit width of int\n");
        return 1;
    }
    unsigned int n = (unsigned int)n_val;

    size_t size = argc - 2;
    int *arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        long val = strtol(argv[i + 2], NULL, 10);
        arr[i] = (int)val;
    }

    int result = count_0th_and_nth_bits(arr, size, n);
    printf("%d\n", result);

    free(arr);
    return 0;
}