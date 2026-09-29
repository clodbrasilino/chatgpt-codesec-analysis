#include <stdio.h>
#include <stdlib.h>

int find_product(const int *list, size_t size, int *result) {
    if (list == NULL || result == NULL || size == 0) {
        return -1;
    }

    int first_even = 0;
    int first_odd = 0;
    int even_found = 0;
    int odd_found = 0;

    for (size_t i = 0; i < size; ++i) {
        if (!even_found && list[i] % 2 == 0) {
            first_even = list[i];
            even_found = 1;
        } else if (!odd_found && list[i] % 2 != 0) {
            first_odd = list[i];
            odd_found = 1;
        }

        if (even_found && odd_found) {
            break;
        }
    }

    if (!even_found || !odd_found) {
        return -1;
    }

    *result = first_even * first_odd;
    return 0;
}

int main(int argc, char * const * const argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <list of integers>\n", argv[0]);
        return 1;
    }

    size_t size = argc - 1;
    int *list = (int *)malloc(size * sizeof(int));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < size; ++i) {
        list[i] = atoi(argv[i + 1]);
    }

    int result;
    if (find_product(list, size, &result) == 0) {
        printf("%d\n", result);
    } else {
        fprintf(stderr, "Invalid input or missing even/odd number\n");
    }

    free(list);
    return 0;
}