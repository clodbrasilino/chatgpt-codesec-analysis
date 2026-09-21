#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  */

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL || *delim == '\0') {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    size_t items_capacity = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    char *temp = (char *)malloc(str_len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, str);

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);
    while (token != NULL) {
        if (tuple->count >= items_capacity) {
            size_t new_capacity = items_capacity == 0 ? 4 : items_capacity * 2;
            char **new_items = (char **)realloc(tuple->items, new_capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t j = 0; j < tuple->count; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                free(temp);
                return NULL;
            }
            tuple->items = new_items;
            items_capacity = new_capacity;
        }

        tuple->items[tuple->count] = strdup(token);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t j = 0; j < tuple->count; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        tuple->count++;
        token = strtok_r(NULL, delim, &rest);
    }

    free(temp);
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

int main(void) {
    const char *input1 = "python3.0";
    const char *delim1 = ".";
    Tuple *t1 = string_to_tuple(input1, delim1);
    if (t1 != NULL) {
        printf("Tuple(%zu): (", t1->count);
        for (size_t i = 0; i < t1->count; i++) {
            printf("'%s'%s", t1->items[i], i < t1->count - 1 ? ", " : "");
        }
        printf(")\n");
        free_tuple(t1);
    }

    const char *input2 = "item1";
    const char *delim2 = "1";
    Tuple *t2 = string_to_tuple(input2, delim2);
    if (t2 != NULL) {
        printf("Tuple(%zu): (", t2->count);
        for (size_t i = 0; i < t2->count; i++) {
            printf("'%s'%s", t2->items[i], i < t2->count - 1 ? ", " : "");
        }
        printf(")\n");
        free_tuple(t2);
    }

    const char *input3 = "1.10";
    const char *delim3 = "1";
    Tuple *t3 = string_to_tuple(input3, delim3);
    if (t3 != NULL) {
        printf("Tuple(%zu): (", t3->count);
        for (size_t i = 0; i < t3->count; i++) {
            printf("'%s'%s", t3->items[i], i < t3->count - 1 ? ", " : "");
        }
        printf(")\n");
        free_tuple(t3);
    }

    return EXIT_SUCCESS;
}