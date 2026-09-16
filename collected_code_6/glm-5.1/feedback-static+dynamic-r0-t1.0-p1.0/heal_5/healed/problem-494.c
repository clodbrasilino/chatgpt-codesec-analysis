#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int binary_tuple_to_int(const unsigned char *tuple, size_t size) {
    if (tuple == NULL && size > 0) {
        return 0;
    }

    if (size == 0) {
        return 0;
    }

    if (size > sizeof(int)) {
        size = sizeof(int);
    }

    int result = 0;

    for (size_t i = 0; i < size; ++i) {
        if (tuple[i] > 1) {
            return 0;
        }
        result = (result << 1) | tuple[i];
    }

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    size_t size = argc - 1;
    unsigned char *tuple = (unsigned char *)malloc(size);

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; ++i) {
        long val = strtol(argv[i + 1], NULL, 10);
        if (val < 0 || val > 255) {
            free(tuple);
            return EXIT_FAILURE;
        }
        tuple[i] = (unsigned char)val;
    }

    int result = binary_tuple_to_int(tuple, size);

    printf("%d\n", result);

    free(tuple);

    return EXIT_SUCCESS;
}