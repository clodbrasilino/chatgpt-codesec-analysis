#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
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

    size_t str_len = strnlen(str, SIZE_MAX);
    char *temp = malloc(str_len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }
    snprintf(temp, str_len + 1, "%s", str);

    size_t delim_span = strspn(temp, delim);

    if (delim_span == str_len) {
        char **new_items = realloc(tuple->items, sizeof(char *));
        if (new_items == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items = new_items;
        tuple->items[tuple->count] = malloc(1);
        if (tuple->items[tuple->count] == NULL) {
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }
        tuple->items[tuple->count][0] = '\0';
        tuple->count++;
        free(temp);
        return tuple;
    }

    char *token = strtok(temp + delim_span, delim);

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
    const char *input2 = "python 3.0";
    const char *delimiter = " ";

    Tuple *my_tuple1 = string_to_tuple(input1, delimiter);
    if (my_tuple1 != NULL) {
        printf("Test 0: [");
        for (size_t i = 0; i < my_tuple1->count; i++) {
            printf("'%s'", my_tuple1->items[i]);
            if (i < my_tuple1->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple1);
    }

    Tuple *my_tuple2 = string_to_tuple(input2, delimiter);
    if (my_tuple2 != NULL) {
        printf("Test 1: [");
        for (size_t i = 0; i < my_tuple2->count; i++) {
            printf("'%s'", my_tuple2->items[i]);
            if (i < my_tuple2->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple2);
    }

    const char *dot_delim = ".";
    Tuple *my_tuple3 = string_to_tuple("5.10", dot_delim);
    if (my_tuple3 != NULL) {
        printf("Test 2: [");
        for (size_t i = 0; i < my_tuple3->count; i++) {
            printf("'%s'", my_tuple3->items[i]);
            if (i < my_tuple3->count - 1) printf(", ");
        }
        printf("]\n");
        free_tuple(my_tuple3);
    }

    return EXIT_SUCCESS;
}