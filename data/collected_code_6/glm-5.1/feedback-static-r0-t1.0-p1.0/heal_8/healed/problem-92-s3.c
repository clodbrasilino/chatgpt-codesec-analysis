#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_undulating(long long num) {
    char *buffer = NULL;
    int len = asprintf(&buffer, "%lld", num);
    
    if (len < 3) {
        free(buffer);
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            free(buffer);
            return 0;
        }
    }

    for (int i = 1; i < len; i++) {
        if (i % 2 == 1) {
            if (buffer[i] == buffer[0]) {
                free(buffer);
                return 0;
            }
        } else {
            if (buffer[i] != buffer[0]) {
                free(buffer);
                return 0;
            }
        }
    }

    free(buffer);
    return 1;
}

int main(int argc, char * const argv[]) {
    long long number;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    number = strtoll(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (is_undulating(number)) {
        printf("Undulating\n");
    } else {
        printf("Not undulating\n");
    }

    return EXIT_SUCCESS;
}