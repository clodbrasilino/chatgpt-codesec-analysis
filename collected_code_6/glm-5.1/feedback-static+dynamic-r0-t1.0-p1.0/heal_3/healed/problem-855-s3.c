#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int check_even_parity(unsigned int num) {
    int count = 0;
    while (num) {
        count ^= (num & 1);
        num >>= 1;
    }
    return count == 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0') {
        printf("False\n");
        return EXIT_SUCCESS;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || val > UINT_MAX) {
        printf("False\n");
        return EXIT_SUCCESS;
    }

    int result = check_even_parity((unsigned int)val);
    printf("%s\n", result ? "True" : "False");

    return EXIT_SUCCESS;
}