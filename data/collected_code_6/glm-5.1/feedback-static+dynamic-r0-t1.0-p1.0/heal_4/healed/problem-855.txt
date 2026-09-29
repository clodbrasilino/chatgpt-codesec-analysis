#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

int check_even_parity(unsigned int num) {
    int parity = 0;
    while (num) {
        parity ^= (num & 1);
        num >>= 1;
    }
    return parity == 0;
}

int main(int argc, char const * const argv[]) {
    if (!isatty(STDIN_FILENO) && argc == 1) {
        char buf[256];
        if (fgets(buf, sizeof(buf), stdin)) {
            char *endptr;
            unsigned long val = strtoul(buf, &endptr, 10);
            if (*endptr != '\0' && *endptr != '\n' && *endptr != '\r') {
                printf("False\n");
                return EXIT_FAILURE;
            }
            if (val > __UINT32_MAX__) {
                printf("False\n");
                return EXIT_FAILURE;
            }
            if (check_even_parity((unsigned int)val)) {
                printf("True\n");
            } else {
                printf("False\n");
            }
            return EXIT_SUCCESS;
        }
    }

    if (argc != 2) {
        printf("False\n");
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val > __UINT32_MAX__) {
        printf("False\n");
        return EXIT_FAILURE;
    }

    if (check_even_parity((unsigned int)val)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return EXIT_SUCCESS;
}