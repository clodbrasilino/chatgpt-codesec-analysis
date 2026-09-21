#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int count;
} StringTuple;

StringTuple* string_list_to_tuple(const char *strings[], int count) {
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (!tuple) return NULL;

    tuple->count = count;
    tuple->strings = (char **)malloc(count * sizeof(char *));
    if (!tuple->strings) {
        free(tuple);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        size_t len = strnlen(strings[i], 1024);
        tuple->strings[i] = (char *)malloc((len + 1) * sizeof(char));
        if (!tuple->strings[i]) {
            while (--i >= 0) {
                free(tuple->strings[i]);
            }
            free(tuple->strings);
            free(tuple);
            return NULL;
        }
        memcpy(tuple->strings[i], strings[i], len);
        tuple->strings[i][len] = '\0';
    }

    return tuple;
}

void free_string_tuple(StringTuple *tuple) {
    if (tuple) {
        for (int i = 0; i < tuple->count; i++) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
        free(tuple);
    }
}

int main() {
    const char *list[] = {"hello", "world", "C", "programming"};
    int count = 4;

    StringTuple *tuple = string_list_to_tuple(list, count);

    if (tuple) {
        for (int i = 0; i < tuple->count; i++) {
            printf("%s\n", tuple->strings[i]);
        }
        free_string_tuple(tuple);
    } else {
        puts("Failed to create tuple");
    }

    return 0;
}