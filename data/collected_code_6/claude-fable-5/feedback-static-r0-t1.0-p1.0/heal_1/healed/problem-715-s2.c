#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t count;
} Tuple;

static int string_to_tuple(const char *str, Tuple *out)
{
    size_t capacity;
    size_t count;
    int *items;
    const char *p;
    char *end;

    if (str == NULL || out == NULL) {
        return -1;
    }

    capacity = 8;
    count = 0;
    items = malloc(capacity * sizeof(int));
    if (items == NULL) {
        return -1;
    }

    p = str;
    while (*p != '\0') {
        long value;

        while (*p != '\0' && (isspace((unsigned char)*p) || *p == ',')) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        errno = 0;
        value = strtol(p, &end, 10);
        if (end == p) {
            free(items);
            return -1;
        }
        if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
            free(items);
            return -1;
        }

        if (count == capacity) {
            size_t new_capacity;
            int *tmp;

            if (capacity > SIZE_MAX / 2) {
                free(items);
                return -1;
            }
            new_capacity = capacity * 2;
            tmp = realloc(items, new_capacity * sizeof(int));
            if (tmp == NULL) {
                free(items);
                return -1;
            }
            items = tmp;
            capacity = new_capacity;
        }

        items[count] = (int)value;
        count++;
        p = end;
    }

    out->items = items;
    out->count = count;
    return 0;
}

static void print_tuple(const Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }

    printf("(");
    for (i = 0; i < t->count; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", t->items[i]);
    }
    printf(")\n");
}

static void free_tuple(Tuple *t)
{
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->count = 0;
    }
}

int main(void)
{
    const char *input = "1, 5, 7, 8, 10";
    Tuple t;

    if (string_to_tuple(input, &t) != 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    print_tuple(&t);
    free_tuple(&t);

    return EXIT_SUCCESS;
}