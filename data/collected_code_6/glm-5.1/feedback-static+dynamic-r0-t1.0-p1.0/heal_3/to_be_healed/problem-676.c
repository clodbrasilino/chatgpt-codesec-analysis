#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_non_alnum(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    const char *p = input;
    size_t input_len = 0;
    while (*p != '\0') {
        input_len++;
        p++;
    }

    char *result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    for (size_t i = 0; i < input_len; i++) {
        if (isalnum((unsigned char)input[i])) {
            result[result_idx++] = input[i];
        }
    }

    result[result_idx] = '\0';

    if (result_idx < input_len) {
        char *trimmed_result = realloc(result, result_idx + 1);
        if (trimmed_result != NULL) {
            result = trimmed_result;
        }
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *cleaned = remove_non_alnum(argv[1]);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return 1;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    return 0;
}