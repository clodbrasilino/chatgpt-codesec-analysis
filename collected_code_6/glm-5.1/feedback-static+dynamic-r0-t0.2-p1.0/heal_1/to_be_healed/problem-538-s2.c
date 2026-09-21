#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple string_list_to_tuple(char **list, size_t count) {
    Tuple tuple;
    tuple.count = count;
    tuple.items = NULL;

    if (count > 0) {
        tuple.items = (char **)malloc(count * sizeof(char *));
        if (tuple.items == NULL) {
            tuple.count = 0;
            return tuple;
        }

        for (size_t i = 0; i < count; i++) {
            if (list[i] != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                tuple.items[i] = (char *)malloc(strlen(list[i]) + 1);
                if (tuple.items[i] == NULL) {
                    for (size_t j = 0; j < i; j++) {
                        free(tuple.items[j]);
                    }
                    free(tuple.items);
                    tuple.items = NULL;
                    tuple.count = 0;
                    return tuple;
                }
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(tuple.items[i], list[i]);
            } else {
                tuple.items[i] = NULL;
            }
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        tuple->items = NULL;
        tuple->count = 0;
    }
}

int main(void) {
    char *list[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(list) / sizeof(list[0]);

    Tuple tuple = string_list_to_tuple(list, count);

    if (tuple.items != NULL) {
        for (size_t i = 0; i < tuple.count; i++) {
            if (tuple.items[i] != NULL) {
                printf("%s\n", tuple.items[i]);
            }
        }
    }

    free_tuple(&tuple);

    return 0;
}