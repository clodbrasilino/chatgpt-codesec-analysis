#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_containing(char ***list, int *size, const char *substr) {
    if (list == NULL || *list == NULL || size == NULL || substr == NULL) {
        return -1;
    }

    int current_size = *size;
    int i = 0;

    while (i < current_size) {
        if ((*list)[i] == NULL || strstr((*list)[i], substr) != NULL) {
            free((*list)[i]);
            for (int j = i; j < current_size - 1; j++) {
                (*list)[j] = (*list)[j + 1];
            }
            current_size--;
        } else {
            i++;
        }
    }

    *size = current_size;

    if (current_size == 0) {
        free(*list);
        *list = NULL;
    } else {
        char **temp = realloc(*list, current_size * sizeof(char *));
        if (temp != NULL) {
            *list = temp;
        }
    }

    return 0;
}

int main(void) {
    int size = 5;
    char **list = malloc(size * sizeof(char *));
    if (list == NULL) {
        return 1;
    }

    const char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        list[i] = malloc(strlen(words[i]) + 1);
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(list[i], words[i]);
    }

    printf("Original list:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    const char *substr = "an";
    int result = remove_words_containing(&list, &size, substr);

    if (result == 0) {
        printf("\nList after removing words containing \"%s\":\n", substr);
        for (int i = 0; i < size; i++) {
            printf("%s\n", list[i]);
        }
    }

    for (int i = 0; i < size; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}