#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return;
    }
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return;
    }
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

/* Possible weaknesses found:
 *  Parameter 'max_lengths' can be declared as pointer to const [constParameterPointer]
 */
void reverse_strings(char **strings, size_t count, size_t *max_lengths) {
    if (strings == NULL || max_lengths == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i], max_lengths[i]);
    }
}

int main(void) {
    const size_t count = 4;
    const char *source_strings[] = {"hello", "reverse", "world", "string"};
    size_t lengths[4];

    for (size_t i = 0; i < count; i++) {
        lengths[i] = strnlen(source_strings[i], 1024) + 1;
    }

    char **list = malloc(count * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        list[i] = NULL;
    }

    for (size_t i = 0; i < count; i++) {
        list[i] = malloc(lengths[i]);
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        if (lengths[i] > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(list[i], source_strings[i], lengths[i] - 1);
            list[i][lengths[i] - 1] = '\0';
        }
    }

    reverse_strings(list, count, lengths);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}