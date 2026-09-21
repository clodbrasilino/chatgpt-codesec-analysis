#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_product_equality(long long n) {
    if (n < 0) {
        n = -n;
    }
    if (n < 10) {
        return 0;
    }

    long long even_product = 1;
    long long odd_product = 1;
    int position = 0;

    while (n > 0) {
        int digit = n % 10;
        if (position % 2 == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }
        position++;
        n /= 10;
    }

    if (even_product == odd_product) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const * argv) {
    long long number;

    if (argc == 2) {
        char *endptr;
        number = strtoll(argv[1], &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
    } else if (argc == 1) {
        char *buffer = NULL;
        size_t len = 0;
        ssize_t read = getline(&buffer, &len, stdin);
        if (read == -1) {
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        char *endptr;
        number = strtoll(buffer, &endptr, 10);
        if (endptr == buffer || (*endptr != '\0' && *endptr != '\n')) {
            free(buffer);
            fprintf(stderr, "Invalid input\n");
            return EXIT_FAILURE;
        }
        free(buffer);
    } else {
        fprintf(stderr, "Usage: %s [number]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (check_product_equality(number)) {
        printf("Equal\n");
    } else {
        printf("Not Equal\n");
    }

    return EXIT_SUCCESS;
}