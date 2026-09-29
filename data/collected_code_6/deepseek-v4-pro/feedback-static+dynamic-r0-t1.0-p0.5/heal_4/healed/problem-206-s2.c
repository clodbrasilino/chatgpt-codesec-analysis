#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    char **items;
    int length;
} Tuple;

typedef struct {
    char **items;
    int length;
} TupleList;

static char *concatenate_strings(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }

    size_t len1 = strnlen(str1, SIZE_MAX);
    size_t len2 = strnlen(str2, SIZE_MAX);

    if (len1 > SIZE_MAX - len2 - 1) {
        return NULL;
    }

    size_t total_len = len1 + len2 + 1;
    char *result = (char *)malloc(total_len);
    if (result == NULL) {
        return NULL;
    }

    if (len1 > 0) {
        memcpy(result, str1, len1);
    }
    if (len2 > 0) {
        memcpy(result + len1, str2, len2);
    }
    result[len1 + len2] = '\0';
    return result;
}

static TupleList *adjacent_concatenation(Tuple *tuples, int tuple_count) {
    if (tuples == NULL || tuple_count <= 0) {
        return NULL;
    }

    TupleList *result = (TupleList *)malloc(sizeof(TupleList));
    if (result == NULL) {
        return NULL;
    }

    int total_pairs = 0;
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i].items == NULL || tuples[i].length < 1) {
            free(result);
            return NULL;
        }
        if (tuples[i].length > 1) {
            if (total_pairs > INT_MAX - (tuples[i].length - 1)) {
                free(result);
                return NULL;
            }
            total_pairs += tuples[i].length - 1;
        }
    }

    if (total_pairs == 0) {
        result->items = NULL;
        result->length = 0;
        return result;
    }

    result->items = (char **)malloc((size_t)total_pairs * sizeof(char *));
    if (result->items == NULL) {
        free(result);
        return NULL;
    }
    result->length = total_pairs;

    int index = 0;
    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < tuples[i].length - 1; j++) {
            if (tuples[i].items[j] == NULL || tuples[i].items[j + 1] == NULL) {
                for (int k = 0; k < index; k++) {
                    free(result->items[k]);
                }
                free(result->items);
                free(result);
                return NULL;
            }
            result->items[index] = concatenate_strings(tuples[i].items[j], tuples[i].items[j + 1]);
            if (result->items[index] == NULL) {
                for (int k = 0; k < index; k++) {
                    free(result->items[k]);
                }
                free(result->items);
                free(result);
                return NULL;
            }
            index++;
        }
    }

    return result;
}

static void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (int i = 0; i < list->length; i++) {
            free(list->items[i]);
        }
        free(list->items);
    }
    free(list);
}

int main(void) {
    char *tuple1_items[] = {"abc", "def", "ghi"};
    char *tuple2_items[] = {"hello", "world"};
    char *tuple3_items[] = {"single"};

    Tuple tuples[] = {
        {tuple1_items, 3},
        {tuple2_items, 2},
        {tuple3_items, 1}
    };

    TupleList *result = adjacent_concatenation(tuples, 3);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < result->length; i++) {
        printf("%s\n", result->items[i]);
    }

    free_tuple_list(result);
    return 0;
}