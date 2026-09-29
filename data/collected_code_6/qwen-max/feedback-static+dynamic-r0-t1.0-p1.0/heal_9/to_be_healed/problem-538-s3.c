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
        const char *str = strings[i];
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = str ? strlen(str) : 0;
        tuple->strings[i] = (char *)malloc((len + 1) * sizeof(char));
        if (!tuple->strings[i]) {
            while (--i >= 0) {
                free(tuple->strings[i]);
            }
            free(tuple->strings);
            free(tuple);
            return NULL;
        }
        if (str) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple->strings[i], str, len);
            tuple->strings[i][len] = '\0';
        } else {
            tuple->strings[i][0] = '\0';
        }
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