#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

    size_t capacity = 2;
    tuple->items = malloc(capacity * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    int split_by_char = 0;
    if (delim == NULL || delim[0] == '\0') {
        split_by_char = 1;
    } else {
        if (strpbrk(str, delim) == NULL) {
            split_by_char = 1;
        }
    }

    if (split_by_char) {
        for (size_t i = 0; str[i] != '\0'; i++) {
            if (tuple->count >= capacity) {
                capacity *= 2;
                char **new_items = realloc(tuple->items, capacity * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t j = 0; j < tuple->count; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tuple);
                    return NULL;
                }
                tuple->items = new_items;
            }
            tuple->items[tuple->count] = malloc(2);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t j = 0; j < tuple->count; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            tuple->items[tuple->count][0] = str[i];
            tuple->items[tuple->count][1] = '\0';
            tuple->count++;
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str) + 1;
        char *tmp = malloc(len);
        if (tmp == NULL) {
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(tmp, str);

        char *token = strtok(tmp, delim);

        while (token != NULL) {
            if (tuple->count >= capacity) {
                capacity *= 2;
                char **new_items = realloc(tuple->items, capacity * sizeof(char *));
                if (new_items == NULL) {
                    for (size_t j = 0; j < tuple->count; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tmp);
                    free(tuple);
                    return NULL;
                }
                tuple->items = new_items;
            }

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t tlen = strlen(token) + 1;
            tuple->items[tuple->count] = malloc(tlen);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t j = 0; j < tuple->count; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tmp);
                free(tuple);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(tuple->items[tuple->count], token);
            tuple->count++;
            token = strtok(NULL, delim);
        }
        free(tmp);
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    free(tuple);
}

int main(int argc, char *argv[]) {
    char *str_buf = calloc(1024, sizeof(char));
    char *delim_buf = calloc(256, sizeof(char));
    if (!str_buf || !delim_buf) {
        free(str_buf);
        free(delim_buf);
        return EXIT_FAILURE;
    }
    
    const char *str = str_buf;
    const char *delim = delim_buf;

    if (argc > 1) {
        str = argv[1];
        if (argc > 2) {
            delim = argv[2];
        }
    } else {
        if (fgets(str_buf, 1024, stdin)) {
            char *nl = strchr(str_buf, '\n');
            if (nl) *nl = '\0';
        }
    }

    Tuple *t = string_to_tuple(str, delim);
    if (t == NULL) {
        free(str_buf);
        free(delim_buf);
        return EXIT_FAILURE;
    }

    printf("[");
    for (size_t i = 0; i < t->count; i++) {
        printf("'%s'", t->items[i]);
        if (i < t->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free_tuple(t);
    free(str_buf);
    free(delim_buf);
    
    return EXIT_SUCCESS;
}