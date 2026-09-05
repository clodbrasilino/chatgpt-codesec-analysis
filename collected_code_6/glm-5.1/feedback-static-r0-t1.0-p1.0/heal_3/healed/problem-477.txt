#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *str_to_lower(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    char *lower_str = malloc(len + 1);
    if (lower_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        lower_str[i] = tolower((unsigned char)str[i]);
    }
    lower_str[len] = '\0';

    return lower_str;
}

int main(int argc, char const * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *result = str_to_lower(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(result);
    return EXIT_SUCCESS;
}