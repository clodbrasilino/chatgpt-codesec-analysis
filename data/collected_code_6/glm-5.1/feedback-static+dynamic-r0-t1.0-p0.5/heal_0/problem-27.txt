#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_digits(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

void free_string_list(char **list, size_t size) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *input[] = {
        "C0ding is f7un",
        "12345",
        "No digits here!",
        "M1x3d 9x8m7p6l5"
    };
    size_t count = sizeof(input) / sizeof(input[0]);

    char **output = malloc(count * sizeof(char *));
    if (output == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        output[i] = remove_digits(input[i]);
        if (output[i] == NULL) {
            free_string_list(output, i);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", output[i]);
    }

    free_string_list(output, count);

    return EXIT_SUCCESS;
}