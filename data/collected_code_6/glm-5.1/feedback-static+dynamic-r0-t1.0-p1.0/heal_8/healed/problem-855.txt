#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

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
        char *buf = malloc(256);
        if (!buf) {
            printf("False\n");
            return EXIT_FAILURE;
        }
        if (fgets(buf, 256, stdin)) {
            if (strchr(buf, '\n') == NULL) {
                int c;
                int max_discard = 1024;
                while ((c = getchar()) != '\n' && c != EOF && max_discard-- > 0) {
                }
                free(buf);
                printf("False\n");
                return EXIT_FAILURE;
            }
            char *endptr;
            unsigned long val = strtoul(buf, &endptr, 10);
            if (*endptr != '\0' && *endptr != '\n' && *endptr != '\r') {
                free(buf);
                printf("False\n");
                return EXIT_FAILURE;
            }
            if (val > __UINT32_MAX__) {
                free(buf);
                printf("False\n");
                return EXIT_FAILURE;
            }
            if (check_even_parity((unsigned int)val)) {
                printf("True\n");
            } else {
                printf("False\n");
            }
            free(buf);
            return EXIT_SUCCESS;
        }
        free(buf);
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