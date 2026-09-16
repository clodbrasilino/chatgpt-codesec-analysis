#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_duplicates(const char *str, char target) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    int found = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == target) {
            if (!found) {
                result[j++] = str[i];
                found = 1;
            }
        } else {
            result[j++] = str[i];
            found = 0;
        }
    }

    result[j] = '\0';
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    char target = argv[2][0];

    char *output = remove_duplicates(input, target);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}