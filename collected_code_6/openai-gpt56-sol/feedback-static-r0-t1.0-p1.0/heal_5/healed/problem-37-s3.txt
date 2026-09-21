#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ITEM_INTEGER,
    ITEM_STRING
} ItemType;

typedef struct {
    ItemType type;
    union {
        int integer;
        char *string;
    } value;
} Item;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);

    if (length == SIZE_MAX) {
        errno = ENOMEM;
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static int compare_items(const void *left, const void *right)
{
    const Item *a = left;
    const Item *b = right;

    if (a->type != b->type) {
        return a->type < b->type ? -1 : 1;
    }

    if (a->type == ITEM_INTEGER) {
        if (a->value.integer < b->value.integer) {
            return -1;
        }

        if (a->value.integer > b->value.integer) {
            return 1;
        }

        return 0;
    }

    if (a->value.string == NULL) {
        return b->value.string == NULL ? 0 : -1;
    }

    if (b->value.string == NULL) {
        return 1;
    }

    return strcmp(a->value.string, b->value.string);
}

static void sort_items(Item *items, size_t count)
{
    if (items != NULL && count > 1U) {
        qsort(items, count, sizeof(*items), compare_items);
    }
}

static void free_items(Item *items, size_t count)
{
    size_t i;

    if (items == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        if (items[i].type == ITEM_STRING) {
            free(items[i].value.string);
            items[i].value.string = NULL;
        }
    }

    free(items);
}

static int parse_integer(const char *text, int *result)
{
    char *end;
    long value;

    if (text == NULL || result == NULL || text[0] == '\0') {
        return 0;
    }

    errno = 0;
    value = strtol(text, &end, 10);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        value < INT_MIN ||
        value > INT_MAX) {
        return 0;
    }

    *result = (int)value;
    return 1;
}

int main(int argc, char *argv[])
{
    Item *items;
    size_t count;
    size_t initialized;
    size_t i;

    if (argc < 2 || argv == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s item...\n", program);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*items)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    items = calloc(count, sizeof(*items));
    if (items == NULL) {
        perror("calloc");
        return EXIT_FAILURE;
    }

    initialized = 0U;

    for (i = 0U; i < count; ++i) {
        const char *argument = argv[i + 1U];
        int value;

        if (argument == NULL) {
            fprintf(stderr, "Invalid null argument\n");
            free_items(items, initialized);
            return EXIT_FAILURE;
        }

        if (parse_integer(argument, &value)) {
            items[i].type = ITEM_INTEGER;
            items[i].value.integer = value;
        } else {
            items[i].type = ITEM_STRING;
            items[i].value.string = duplicate_string(argument);

            if (items[i].value.string == NULL) {
                fprintf(stderr, "Failed to allocate memory\n");
                free_items(items, initialized + 1U);
                return EXIT_FAILURE;
            }
        }

        ++initialized;
    }

    sort_items(items, count);

    for (i = 0U; i < count; ++i) {
        int status;

        if (items[i].type == ITEM_INTEGER) {
            status = printf("%d\n", items[i].value.integer);
        } else {
            status = printf("%s\n", items[i].value.string);
        }

        if (status < 0) {
            fprintf(stderr, "Output error\n");
            free_items(items, count);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF || ferror(stdout)) {
        fprintf(stderr, "Output error\n");
        free_items(items, count);
        return EXIT_FAILURE;
    }

    free_items(items, count);
    return EXIT_SUCCESS;
}