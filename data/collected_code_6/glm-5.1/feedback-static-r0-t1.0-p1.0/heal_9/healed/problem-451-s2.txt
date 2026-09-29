#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_whitespaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, SIZE_MAX);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    const char *p = str;

    while (*p) {
        if (!isspace((unsigned char)*p)) {
            result[res_idx++] = *p;
        }
        p++;
    }

    result[res_idx] = '\0';

    char *shrunk = realloc(result, res_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t argv_len = strnlen(argv[1], SIZE_MAX);
    char *safe_arg = malloc(argv_len + 1);
    if (safe_arg == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }
    
    memcpy(safe_arg, argv[1], argv_len + 1);

    char *cleaned = remove_whitespaces(safe_arg);
    free(safe_arg);

    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);
    free(cleaned);
    return EXIT_SUCCESS;
}