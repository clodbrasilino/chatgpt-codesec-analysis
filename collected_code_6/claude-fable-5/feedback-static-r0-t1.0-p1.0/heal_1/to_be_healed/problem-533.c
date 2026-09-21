#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        int i;
        double d;
        char *s;
    } value;
} Element;

typedef struct {
    Element *items;
    size_t size;
} Tuple;

static int tuple_init(Tuple *t, size_t capacity)
{
    if (t == NULL) {
        return -1;
    }
    t->items = NULL;
    t->size = 0;
    if (capacity == 0) {
        return 0;
    }
    t->items = calloc(capacity, sizeof(Element));
    if (t->items == NULL) {
        return -1;
    }
    return 0;
}

static void tuple_free(Tuple *t)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'idx' can be reduced. [variableScope]
     */
    size_t idx;

    if (t == NULL) {
        return;
    }
    if (t->items != NULL) {
        for (idx = 0; idx < t->size; idx++) {
            if (t->items[idx].type == TYPE_STRING) {
                free(t->items[idx].value.s);
                t->items[idx].value.s = NULL;
            }
        }
        free(t->items);
        t->items = NULL;
    }
    t->size = 0;
}

static int tuple_add_int(Tuple *t, size_t capacity, int v)
{
    if (t == NULL || t->items == NULL || t->size >= capacity) {
        return -1;
    }
    t->items[t->size].type = TYPE_INT;
    t->items[t->size].value.i = v;
    t->size++;
    return 0;
}

static int tuple_add_double(Tuple *t, size_t capacity, double v)
{
    if (t == NULL || t->items == NULL || t->size >= capacity) {
        return -1;
    }
    t->items[t->size].type = TYPE_DOUBLE;
    t->items[t->size].value.d = v;
    t->size++;
    return 0;
}

static int tuple_add_string(Tuple *t, size_t capacity, const char *v)
{
    size_t len;
    char *copy;

    if (t == NULL || t->items == NULL || v == NULL || t->size >= capacity) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(v);
    copy = malloc(len + 1U);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, v, len + 1U);
    t->items[t->size].type = TYPE_STRING;
    t->items[t->size].value.s = copy;
    t->size++;
    return 0;
}

static int remove_type_elements(const Tuple *src, Tuple *dst, ElementType remove_type)
{
    size_t idx;
    size_t kept = 0;

    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (tuple_init(dst, src->size == 0 ? 1 : src->size) != 0) {
        return -1;
    }
    for (idx = 0; idx < src->size; idx++) {
        if (src->items[idx].type == remove_type) {
            continue;
        }
        switch (src->items[idx].type) {
        case TYPE_INT:
            if (tuple_add_int(dst, src->size, src->items[idx].value.i) != 0) {
                tuple_free(dst);
                return -1;
            }
            break;
        case TYPE_DOUBLE:
            if (tuple_add_double(dst, src->size, src->items[idx].value.d) != 0) {
                tuple_free(dst);
                return -1;
            }
            break;
        case TYPE_STRING:
            if (tuple_add_string(dst, src->size, src->items[idx].value.s) != 0) {
                tuple_free(dst);
                return -1;
            }
            break;
        default:
            tuple_free(dst);
            return -1;
        }
        kept++;
    }
    (void)kept;
    return 0;
}

static void tuple_print(const Tuple *t)
{
    size_t idx;

    if (t == NULL || t->items == NULL) {
        printf("()\n");
        return;
    }
    printf("(");
    for (idx = 0; idx < t->size; idx++) {
        switch (t->items[idx].type) {
        case TYPE_INT:
            printf("%d", t->items[idx].value.i);
            break;
        case TYPE_DOUBLE:
            printf("%f", t->items[idx].value.d);
            break;
        case TYPE_STRING:
            printf("'%s'", t->items[idx].value.s);
            break;
        default:
            printf("?");
            break;
        }
        if (idx + 1U < t->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    Tuple original;
    Tuple filtered;
    const size_t capacity = 6;

    if (tuple_init(&original, capacity) != 0) {
        fprintf(stderr, "Allocation failure\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_int(&original, capacity, 10) != 0 ||
        tuple_add_string(&original, capacity, "hello") != 0 ||
        tuple_add_double(&original, capacity, 3.14) != 0 ||
        tuple_add_int(&original, capacity, 42) != 0 ||
        tuple_add_string(&original, capacity, "world") != 0 ||
        tuple_add_double(&original, capacity, 2.71) != 0) {
        fprintf(stderr, "Failed to build tuple\n");
        tuple_free(&original);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    tuple_print(&original);

    if (remove_type_elements(&original, &filtered, TYPE_STRING) != 0) {
        fprintf(stderr, "Failed to filter tuple\n");
        tuple_free(&original);
        return EXIT_FAILURE;
    }

    printf("After removing strings: ");
    tuple_print(&filtered);

    tuple_free(&filtered);

    if (remove_type_elements(&original, &filtered, TYPE_INT) != 0) {
        fprintf(stderr, "Failed to filter tuple\n");
        tuple_free(&original);
        return EXIT_FAILURE;
    }

    printf("After removing ints: ");
    tuple_print(&filtered);

    tuple_free(&filtered);
    tuple_free(&original);

    return EXIT_SUCCESS;
}