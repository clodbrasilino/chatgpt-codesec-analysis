#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int is_hex_even(const char *hex_str) {
    if (hex_str == NULL) {
        return -1;
    }

    char *endptr;
    long val;
    errno = 0;

    val = strtol(hex_str, &endptr, 16);

    if (errno == ERANGE || endptr == hex_str || *endptr != '\0') {
        return -1;
    }

    if ((val & 1) == 0) {
        return 1;
    }

    return 0;
}

int main(void) {
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (buffer[strcspn(buffer, "\n")] != '\n') {
        free(buffer);
        return EXIT_FAILURE;
    }
    buffer[strcspn(buffer, "\n")] = '\0';

    int result = is_hex_even(buffer);

    if (result == 1) {
        printf("Even\n");
    } else if (result == 0) {
        printf("Odd\n");
    } else {
        printf("Invalid\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}