#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t remove_words(char **list, size_t size, const char *substr) {
    if (list == NULL || substr == NULL) {
        return 0;
    }
    size_t new_size = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL || strstr(list[i], substr) == NULL) {
            list[new_size++] = list[i];
        } else {
            free(list[i]);
        }
    }
    for (size_t i = new_size; i < size; i++) {
        list[i] = NULL;
    }
    return new_size;
}

int main(void) {
    const char *src[] = {"hello", "world", "test", "apple", "banana"};
    size_t count = sizeof(src) / sizeof(src[0]);

    char **list = malloc(count * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        list[i] = malloc(strlen(src[i]) + 1);
        if (list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(list[i], src[i]);
    }

    size_t new_count = remove_words(list, count, "a");

    for (size_t i = 0; i < new_count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < new_count; i++) {
        free(list[i]);
    }
    free(list);

    return EXIT_SUCCESS;
}