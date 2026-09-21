#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        free(tuple);
    }
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        free_tuple(tuple);
        return NULL;
    }

    size_t buf_idx = 0;

    for (size_t i = 0; i < len; i++) {
        if (strchr(delim, str[i]) != NULL) {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                
                char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
                if (new_items == NULL) {
                    free(buffer);
                    free_tuple(tuple);
                    return NULL;
                }
                tuple->items = new_items;

                tuple->items[tuple->count] = malloc(buf_idx + 1);
                if (tuple->items[tuple->count] == NULL) {
                    free(buffer);
                    free_tuple(tuple);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(tuple->items[tuple->count], buffer, buf_idx + 1);
                tuple->count++;
                buf_idx = 0;
            }
        } else {
            buffer[buf_idx++] = str[i];
        }
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        
        char **new_items = realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            free(buffer);
            free_tuple(tuple);
            return NULL;
        }
        tuple->items = new_items;

        tuple->items[tuple->count] = malloc(buf_idx + 1);
        if (tuple->items[tuple->count] == NULL) {
            free(buffer);
            free_tuple(tuple);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->items[tuple->count], buffer, buf_idx + 1);
        tuple->count++;
    }

    free(buffer);
    
    if (tuple->count == 0) {
        free_tuple(tuple);
        return NULL;
    }

    return tuple;
}

int main(void) {
    const char *input1 = "python3.0";
    const char *input2 = "item1";
    const char *input3 = "15.10";
    const char *delim = ".";

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