#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got []
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got []
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got []
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

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

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
        
        tuple->items[tuple->count] = strdup(token);
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
        token = strtok(NULL, delim);
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
    const char *input = "apple,banana,cherry";
    const char *delim = ",";

    Tuple *my_tuple = string_to_tuple(input, delim);
    if (my_tuple == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < my_tuple->count; i++) {
        printf("%zu: %s\n", i, my_tuple->items[i]);
    }

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}