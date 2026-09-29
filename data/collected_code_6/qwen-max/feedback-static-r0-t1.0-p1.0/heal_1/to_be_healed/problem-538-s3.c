#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int count;
} StringTuple;

/* Possible weaknesses found:
 *  Parameter 'strings' can be declared as const array [constParameter]
 */
StringTuple* string_list_to_tuple(char *strings[], int count) {
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (!tuple) return NULL;

    tuple->count = count;
    tuple->strings = (char **)malloc(count * sizeof(char *));
    if (!tuple->strings) {
        free(tuple);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
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
        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
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
    char *list[] = {"hello", "world", "C", "programming"};
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