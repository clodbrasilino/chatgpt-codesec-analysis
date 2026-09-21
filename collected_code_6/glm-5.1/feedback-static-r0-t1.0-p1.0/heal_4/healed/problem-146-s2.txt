#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 1024

size_t find_total_ascii(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }

    size_t total = 0;
    size_t i = 0;

    while (i < max_len && str[i] != '\0') {
        total += (unsigned char)str[i];
        i++;
    }

    return total;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(argv[1], MAX_INPUT_LEN);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }

    memcpy(buffer, argv[1], len + 1);

    size_t result = find_total_ascii(buffer, len + 1);
    printf("%zu\n", result);

    free(buffer);

    return EXIT_SUCCESS;
}