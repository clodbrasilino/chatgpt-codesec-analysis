#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(char **list, int count) {
    if (list == NULL || count <= 0) return;
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]);
            char *temp_str = malloc((len + 1) * sizeof(char));
            if (temp_str == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(temp_str, list[i], len + 1);
            reverse_string(temp_str, len);
            free(list[i]);
            list[i] = temp_str;
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    char **alloc_strings = malloc(count * sizeof(char *));
    if (alloc_strings == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        alloc_strings[i] = strdup(strings[i]);
        if (alloc_strings[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
    }

    reverse_strings_in_list(alloc_strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", alloc_strings[i]);
        free(alloc_strings[i]);
    }
    free(alloc_strings);

    return 0;
}