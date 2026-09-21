#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} StringTuple;

static char *safe_strdup(const char *str) {
    size_t len;
    char *copy;
    
    if (str == NULL) {
        return NULL;
    }
    
    len = strnlen(str, 4096);
    copy = (char *)malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        memmove(copy, str, len);
    }
    copy[len] = '\0';
    return copy;
}

StringTuple concat_string_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    StringTuple result;
    size_t i;

    if (tuple1 == NULL || tuple2 == NULL) {
        result.items = NULL;
        result.length = 0;
        return result;
    }

    result.length = tuple1->length + tuple2->length;
    result.items = (char **)calloc(result.length, sizeof(char *));

    if (result.items == NULL) {
        result.length = 0;
        return result;
    }

    for (i = 0; i < tuple1->length; i++) {
        if (tuple1->items[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
        result.items[i] = safe_strdup(tuple1->items[i]);
        if (result.items[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
    }

    for (i = 0; i < tuple2->length; i++) {
        size_t index = tuple1->length + i;
        if (tuple2->items[i] == NULL) {
            size_t j;
            for (j = 0; j < index; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
        result.items[index] = safe_strdup(tuple2->items[i]);
        if (result.items[index] == NULL) {
            size_t j;
            for (j = 0; j < index; j++) {
                free(result.items[j]);
            }
            free(result.items);
            result.items = NULL;
            result.length = 0;
            return result;
        }
    }

    return result;
}

void free_string_tuple(StringTuple *tuple) {
    size_t i;

    if (tuple == NULL || tuple->items == NULL) {
        return;
    }

    for (i = 0; i < tuple->length; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->length = 0;
}

int main(void) {
    char *items1[] = {"hello", "world"};
    char *items2[] = {"foo", "bar", "baz"};
    StringTuple tuple1;
    StringTuple tuple2;
    StringTuple result;
    size_t i;

    tuple1.items = items1;
    tuple1.length = sizeof(items1) / sizeof(items1[0]);
    tuple2.items = items2;
    tuple2.length = sizeof(items2) / sizeof(items2[0]);

    result = concat_string_tuples(&tuple1, &tuple2);

    if (result.items == NULL) {
        printf("Concatenation failed\n");
        return 1;
    }

    for (i = 0; i < result.length; i++) {
        printf("%s\n", result.items[i]);
    }

    free_string_tuple(&result);

    return 0;
}