#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple *list_to_tuple(const char **list, size_t count) {
    Tuple *t = NULL;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
     */
    size_t i = 0;

    if (list == NULL && count > 0) {
        return NULL;
    }

    t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->count = count;
    t->items = NULL;

    if (count > 0) {
        t->items = calloc(count, sizeof(char *));
        if (t->items == NULL) {
            free(t);
            return NULL;
        }

        for (i = 0; i < count; i++) {
            if (list[i] == NULL) {
                t->items[i] = NULL;
                continue;
            }
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]) + 1;
            t->items[i] = malloc(len);
            if (t->items[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(t->items[j]);
                }
                free(t->items);
                free(t);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(t->items[i], list[i], len);
        }
    }

    return t;
}

void free_tuple(Tuple *t) {
    if (t == NULL) {
        return;
    }
    if (t->items != NULL) {
        for (size_t i = 0; i < t->count; i++) {
            free(t->items[i]);
        }
        free(t->items);
    }
    free(t);
}

void print_tuple(const Tuple *t) {
    if (t == NULL) {
        printf("()\n");
        return;
    }
    printf("(");
    for (size_t i = 0; i < t->count; i++) {
        if (t->items[i] != NULL) {
            printf("'%s'", t->items[i]);
        } else {
            printf("NULL");
        }
        if (i + 1 < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    const char *list[] = {"apple", "banana", "cherry"};
    size_t count = sizeof(list) / sizeof(list[0]);

    Tuple *t = list_to_tuple(list, count);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(t);
    free_tuple(t);

    return EXIT_SUCCESS;
}