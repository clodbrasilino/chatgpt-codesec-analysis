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

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    size_t delim_len = strlen(delim);
    if (delim_len == 0) {
        tuple->items = malloc(sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
        tuple->items[0] = strdup(str);
        if (tuple->items[0] == NULL) {
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        tuple->count = 1;
        return tuple;
    }

    char *temp = strdup(str);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);
    while (token != NULL) {
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
        token = strtok_r(NULL, delim, &rest);
    }

    if (tuple->count == 0) {
        tuple->items = malloc(sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items[0] = strdup(str);
        if (tuple->items[0] == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->count = 1;
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
    const char *input2 = "item1";
    const char *input3 = "1.5.10";
    const char *delim = ".";

    Tuple *my_tuple1 = string_to_tuple(input1, delim);
    if (my_tuple1 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple1->count; i++) {
            for (size_t j = 0; j < strlen(my_tuple1->items[i]); j++) {
                printf("'%c'", my_tuple1->items[i][j]);
                if (i < my_tuple1->count - 1 || j < strlen(my_tuple1->items[i]) - 1) printf(", ");
            }
        }
        printf("]\n");
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delim);
    if (my_tuple2 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple2->count; i++) {
            for (size_t j = 0; j < strlen(my_tuple2->items[i]); j++) {
                printf("'%c'", my_tuple2->items[i][j]);
                if (i < my_tuple2->count - 1 || j < strlen(my_tuple2->items[i]) - 1) printf(", ");
            }
        }
        printf("]\n");
        free_tuple(my_tuple2);
    }

    Tuple *my_tuple3 = string_to_tuple(input3, delim);
    if (my_tuple3 != NULL) {
        printf("[");
        for (size_t i = 0; i < my_tuple3->count; i++) {
            for (size_t j = 0; j < strlen(my_tuple3->items[i]); j++) {
                printf("'%c'", my_tuple3->items[i][j]);
                if (i < my_tuple3->count - 1 || j < strlen(my_tuple3->items[i]) - 1) printf(", ");
            }
        }
        printf("]\n");
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}