#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_index_chars(const char *str) {
    if (str == NULL) {
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(str);
    char *result = malloc(len / 2 + 2);
    if (result == NULL) {
        exit(EXIT_FAILURE);
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *input = "abcdefghijklmnopqrstuvwxyz";
    char *output = remove_odd_index_chars(input);

    printf("%s\n", output);
    free(output);

    char *test_result = remove_odd_index_chars(NULL);

    if (test_result == NULL) {
        printf("NULL input handled correctly.\n");
    } else {
        free(test_result);
    }

    return 0;
}