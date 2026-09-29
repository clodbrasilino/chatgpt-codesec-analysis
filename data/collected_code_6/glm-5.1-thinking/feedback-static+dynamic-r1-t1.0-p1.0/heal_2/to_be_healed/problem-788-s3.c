#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t count;
} List;

typedef struct {
    char *string;
    List list;
} Tuple;

void free_tuple(Tuple *t) {
    if (t == NULL) {
        return;
    }
    free(t->list.items);
    free(t->string);
    free(t);
}

Tuple *create_tuple(const char *str, const int *items, size_t count) {
    if (str == NULL || (items == NULL && count > 0)) {
        return NULL;
    }

    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }

    t->string = strdup(str);
    if (t->string == NULL) {
        free(t);
        return NULL;
    }

    t->list.count = count;
    if (count > 0) {
        if (count > SIZE_MAX / sizeof(int)) {
            free(t->string);
            free(t);
            return NULL;
        }
        t->list.items = malloc(count * sizeof(int));
        if (t->list.items == NULL) {
            free(t->string);
            free(t);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t->list.items, items, count * sizeof(int));
    } else {
        t->list.items = NULL;
    }

    return t;
}

int main(void) {
    const char *str = "example_string";
    int items[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(items) / sizeof(items[0]);

    Tuple *t = create_tuple(str, items, count);
    if (t == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return EXIT_FAILURE;
    }

    printf("Tuple string: %s\n", t->string);
    printf("Tuple list items: ");
    for (size_t i = 0; i < t->list.count; i++) {
        printf("%d ", t->list.items[i]);
    }
    printf("\n");

    free_tuple(t);

    return EXIT_SUCCESS;
}