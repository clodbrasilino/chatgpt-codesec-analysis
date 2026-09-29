#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *const *strings;
    int count;
} StringTuple;

StringTuple* string_list_to_tuple(const char *strings[], int count) {
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (!tuple) return NULL;

    tuple->count = count;
    tuple->strings = (char *const *)malloc(count * sizeof(char *));
    if (!tuple->strings) {
        free(tuple);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         *  read-only variable is not assignable
         *  assignment of read-only location '*(tuple->strings + (sizetype)((long unsigned int)i * 8))'
         */
        tuple->strings[i] = (char *)malloc((strlen(strings[i]) + 1) * sizeof(char));
        if (!tuple->strings[i]) {
            while (--i >= 0) {
                free(tuple->strings[i]);
            }
            free(tuple->strings);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->strings[i], strings[i]);
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