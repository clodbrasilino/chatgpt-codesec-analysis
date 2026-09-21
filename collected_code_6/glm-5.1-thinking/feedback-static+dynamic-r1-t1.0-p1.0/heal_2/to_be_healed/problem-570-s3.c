#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_containing(char ***list, int *size, const char *substr) {
    if (list == NULL || *list == NULL || size == NULL || substr == NULL) {
        return -1;
    }

    int current_size = *size;
    int write_idx = 0;

    for (int read_idx = 0; read_idx < current_size; read_idx++) {
        if ((*list)[read_idx] != NULL && strstr((*list)[read_idx], substr) == NULL) {
            (*list)[write_idx++] = (*list)[read_idx];
        } else {
            free((*list)[read_idx]);
        }
    }

    current_size = write_idx;
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
        size_t len = strlen(words[i]);
        list[i] = malloc(len + 1);
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
        snprintf(list[i], len + 1, "%s", words[i]);
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