#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *string_to_upper(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        result[i] = (char)toupper((unsigned char)str[i]);
    }
    result[len] = '\0';

    return result;
}

int main(void) {
    const char *input = "Hello, World! 123";
    char *upper = string_to_upper(input);

    if (upper != NULL) {
        printf("%s\n", upper);
        free(upper);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}