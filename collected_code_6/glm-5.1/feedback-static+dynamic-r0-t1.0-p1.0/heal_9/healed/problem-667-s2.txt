#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t count_vowels(const char *str) {
    size_t count = 0;
    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'A': case 'E': case 'I': case 'O': case 'U':
                count++;
                break;
            default:
                break;
        }
    }
    return count;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t max_len = 1024;
    size_t len = strnlen(input, max_len);
    if (len >= max_len) {
        fprintf(stderr, "Error: Input string excessively long\n");
        return EXIT_FAILURE;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    memcpy(buffer, input, len + 1);
    buffer[len] = '\0';
    size_t vowels = count_vowels(buffer);
    printf("%zu\n", vowels);
    free(buffer);

    return EXIT_SUCCESS;
}