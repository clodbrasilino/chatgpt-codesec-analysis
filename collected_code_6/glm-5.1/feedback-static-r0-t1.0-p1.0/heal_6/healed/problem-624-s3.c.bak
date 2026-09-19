#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *string_to_upper(const char *str) {
    size_t len;
    char *result;
    size_t i;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        result[i] = (char)toupper((unsigned char)str[i]);
    }

    result[len] = '\0';

    return result;
}

int main(int argc, char const * const argv[const]) {
    char *upper_str;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upper_str = string_to_upper(argv[1]);
    if (upper_str == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", upper_str);

    free(upper_str);
    upper_str = NULL;

    return EXIT_SUCCESS;
}