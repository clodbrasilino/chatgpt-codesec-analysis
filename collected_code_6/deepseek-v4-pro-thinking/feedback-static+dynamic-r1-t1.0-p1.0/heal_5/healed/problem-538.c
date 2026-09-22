#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t length;
} StringTuple;

#define MAX_STRING_LENGTH 4096

void free_string_tuple(StringTuple *tuple) {
    if (tuple == NULL) return;
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->length; ++i) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        tuple->items = NULL;
    }
    tuple->length = 0;
}

static size_t safe_strlen(const char *str, size_t maxlen) {
    const char *p = memchr(str, '\0', maxlen);
    return p ? (size_t)(p - str) : maxlen;
}

StringTuple string_list_to_tuple(char **list, size_t count) {
    StringTuple tuple = { NULL, 0 };
    if (count == 0 || list == NULL) {
        return tuple;
    }
    if (count > SIZE_MAX / sizeof(char *)) {
        return tuple;
    }
    tuple.items = malloc(count * sizeof(char *));
    if (tuple.items == NULL) {
        return tuple;
    }
    tuple.length = count;
    for (size_t i = 0; i < count; ++i) {
        if (list[i] == NULL) {
            free_string_tuple(&tuple);
            return (StringTuple){ NULL, 0 };
        }
        size_t len = safe_strlen(list[i], MAX_STRING_LENGTH);
        if (len == MAX_STRING_LENGTH) {
            free_string_tuple(&tuple);
            return (StringTuple){ NULL, 0 };
        }
        tuple.items[i] = malloc(len + 1);
        if (tuple.items[i] == NULL) {
            free_string_tuple(&tuple);
            return (StringTuple){ NULL, 0 };
        }
        for (size_t j = 0; j <= len; ++j) {
            tuple.items[i][j] = list[i][j];
        }
    }
    return tuple;
}

int main(void) {
    char *list[] = { "hello", "world", "example" };
    size_t count = sizeof(list) / sizeof(list[0]);
    StringTuple tuple = string_list_to_tuple(list, count);
    if (tuple.items == NULL) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%s\n", tuple.items[i]);
    }
    free_string_tuple(&tuple);
    return EXIT_SUCCESS;
}