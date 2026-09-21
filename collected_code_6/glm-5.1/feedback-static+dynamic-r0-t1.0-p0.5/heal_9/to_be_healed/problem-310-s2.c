#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->items = NULL;
    tuple->count = 0;

    if (*delim == '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t str_len = strlen(str);
        if (str_len > 0) {
            tuple->items = malloc(str_len * sizeof(char *));
            if (tuple->items == NULL) {
                free(tuple);
                return NULL;
            }
            for (size_t i = 0; i < str_len; i++) {
                tuple->items[i] = malloc(2);
                if (tuple->items[i] == NULL) {
                    for (size_t j = 0; j < i; j++) {
                        free(tuple->items[j]);
                    }
                    free(tuple->items);
                    free(tuple);
                    return NULL;
                }
                tuple->items[i][0] = str[i];
                tuple->items[i][1] = '\0';
            }
            tuple->count = str_len;
        }
        return tuple;
    }

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

    char *rest = temp;
    char *token;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t delim_len = strlen(delim);

    while (1) {
        if (delim_len == 1) {
            token = strtok_r(rest, (char *)delim, &rest);
        } else {
            token = strstr(rest, delim);
        }

        if (token == NULL) {
            break;
        }

        char *item_str;
        if (delim_len == 1) {
            item_str = token;
        } else {
            size_t token_len = token - rest;
            item_str = malloc(token_len + 1);
            if (item_str == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            if (token_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(item_str, rest, token_len);
            }
            item_str[token_len] = '\0';
            rest = token + delim_len;
        }

        char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            if (delim_len > 1) {
                free(item_str);
            }
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        
        if (delim_len == 1) {
            tuple->items[tuple->count] = strdup(item_str);
            if (tuple->items[tuple->count] == NULL) {
                for (size_t i = 0; i < tuple->count; i++) {
                    free(tuple->items[i]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
        } else {
            tuple->items[tuple->count] = item_str;
        }

        tuple->count++;
    }

    if (delim_len > 1 && *rest != '\0') {
        char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[tuple->count] = strdup(rest);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count++;
    }

    free(temp);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        free(tuple);
    }
}

int main(void) {
    const char *inputs[] = {"python3.0", "item1", "15.10"};
    const char *delimiter = "";

    for (int i = 0; i < 3; i++) {
        Tuple *my_tuple = string_to_tuple(inputs[i], delimiter);
        if (my_tuple == NULL) {
            fprintf(stderr, "Failed to convert string to tuple\n");
            return EXIT_FAILURE;
        }

        printf("[");
        for (size_t j = 0; j < my_tuple->count; j++) {
            printf("'%s'", my_tuple->items[j]);
            if (j < my_tuple->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        free_tuple(my_tuple);
    }

    const char *csv = "apple,banana,cherry";
    Tuple *csv_tuple = string_to_tuple(csv, ",");
    if (csv_tuple != NULL) {
        printf("[");
        for (size_t j = 0; j < csv_tuple->count; j++) {
            printf("'%s'", csv_tuple->items[j]);
            if (j < csv_tuple->count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_tuple(csv_tuple);
    }

    return EXIT_SUCCESS;
}