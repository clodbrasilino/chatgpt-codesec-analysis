#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (camel_str[len] != '\0') len++;

    size_t max_len = len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && isupper((unsigned char)camel_str[i]) && islower((unsigned char)camel_str[i - 1])) {
            if (j >= max_len - 1) break;
            result[j++] = '_';
        }
        if (j >= max_len - 1) break;
        result[j++] = tolower((unsigned char)camel_str[i]);
    }
    result[j] = '\0';

    size_t final_len = j + 1;
    char *final_str = malloc(final_len);
    if (final_str == NULL) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < final_len; i++) {
        final_str[i] = result[i];
    }

    free(result);

    return final_str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camel_case_string>\n", argv[0]);
        return 1;
    }

    char *snake_str = camel_to_snake(argv[1]);
    if (snake_str == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    printf("%s\n", snake_str);

    free(snake_str);
    return 0;
}