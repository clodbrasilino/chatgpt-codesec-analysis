#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  */

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *temp = (char *)malloc(len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(temp, str);

    char *token = strtok(temp, delim);
    while (token != NULL) {
        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
        tuple->items[tuple->count] = (char *)malloc(token_len + 1);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(tuple->items[tuple->count], token);
        tuple->count++;

        token = strtok(NULL, delim);
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
    const char *input1 = "python3.0";
    const char *input2 = "item1";
    const char *input3 = "15.10";
    const char *delim = ",";

    Tuple *my_tuple1 = string_to_tuple(input1, delim);
    if (my_tuple1 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple1->count; i++) {
            printf("'%s'", my_tuple1->items[i]);
            if (i < my_tuple1->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delim);
    if (my_tuple2 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple2->count; i++) {
            printf("'%s'", my_tuple2->items[i]);
            if (i < my_tuple2->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple(input3, delim);
    if (my_tuple3 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple3->count; i++) {
            printf("'%s'", my_tuple3->items[i]);
            if (i < my_tuple3->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}