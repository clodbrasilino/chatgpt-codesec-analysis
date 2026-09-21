#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096U

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        int i;
        double f;
        char *s;
    } value;
} Element;

typedef struct {
    Element *items;
    size_t count;
    size_t capacity;
} Tuple;

static int tuple_init(Tuple *t, size_t capacity)
{
    if (t == NULL || capacity == 0U) {
        return -1;
    }
    t->items = calloc(capacity, sizeof(Element));
    if (t->items == NULL) {
        t->count = 0U;
        t->capacity = 0U;
        return -1;
    }
    t->count = 0U;
    t->capacity = capacity;
    return 0;
}

static int tuple_add_int(Tuple *t, int v)
{
    if (t == NULL || t->items == NULL || t->count >= t->capacity) {
        return -1;
    }
    t->items[t->count].type = TYPE_INT;
    t->items[t->count].value.i = v;
    t->count++;
    return 0;
}

static int tuple_add_float(Tuple *t, double v)
{
    if (t == NULL || t->items == NULL || t->count >= t->capacity) {
        return -1;
    }
    t->items[t->count].type = TYPE_FLOAT;
    t->items[t->count].value.f = v;
    t->count++;
    return 0;
}

static int tuple_add_string(Tuple *t, const char *v)
{
    char *copy;
    size_t len;
    size_t alloc_size;

    if (t == NULL || v == NULL || t->items == NULL || t->count >= t->capacity) {
        return -1;
    }
    len = strnlen(v, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return -1;
    }
    alloc_size = len + 1U;
    if (alloc_size < len) {
        return -1;
    }
    copy = malloc(alloc_size);
    if (copy == NULL) {
        return -1;
    }
    memcpy(copy, v, len);
    copy[len] = '\0';
    t->items[t->count].type = TYPE_STRING;
    t->items[t->count].value.s = copy;
    t->count++;
    return 0;
}

static void tuple_free(Tuple *t)
{
    if (t == NULL) {
        return;
    }
    if (t->items != NULL) {
        for (size_t i = 0U; i < t->count; i++) {
            if (t->items[i].type == TYPE_STRING && t->items[i].value.s != NULL) {
                free(t->items[i].value.s);
                t->items[i].value.s = NULL;
            }
        }
        free(t->items);
        t->items = NULL;
    }
    t->count = 0U;
    t->capacity = 0U;
}

static int tuple_remove_type(Tuple *t, ElementType type)
{
    size_t write_idx;

    if (t == NULL || t->items == NULL) {
        return -1;
    }
    write_idx = 0U;
    for (size_t read_idx = 0U; read_idx < t->count; read_idx++) {
        if (t->items[read_idx].type == type) {
            if (type == TYPE_STRING && t->items[read_idx].value.s != NULL) {
                free(t->items[read_idx].value.s);
                t->items[read_idx].value.s = NULL;
            }
        } else {
            if (write_idx != read_idx) {
                t->items[write_idx] = t->items[read_idx];
            }
            write_idx++;
        }
    }
    t->count = write_idx;
    return 0;
}

static void tuple_print(const Tuple *t)
{
    if (t == NULL || t->items == NULL) {
        printf("(empty)\n");
        return;
    }
    printf("(");
    for (size_t i = 0U; i < t->count; i++) {
        switch (t->items[i].type) {
        case TYPE_INT:
            printf("%d", t->items[i].value.i);
            break;
        case TYPE_FLOAT:
            printf("%.2f", t->items[i].value.f);
            break;
        case TYPE_STRING:
            if (t->items[i].value.s != NULL) {
                printf("\"%s\"", t->items[i].value.s);
            }
            break;
        default:
            break;
        }
        if (i + 1U < t->count) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    Tuple t;

    if (tuple_init(&t, 8U) != 0) {
        fprintf(stderr, "Failed to initialize tuple\n");
        return EXIT_FAILURE;
    }

    if (tuple_add_int(&t, 4) != 0 ||
        tuple_add_float(&t, 5.5) != 0 ||
        tuple_add_string(&t, "hello") != 0 ||
        tuple_add_int(&t, 7) != 0 ||
        tuple_add_string(&t, "world") != 0 ||
        tuple_add_float(&t, 2.25) != 0) {
        fprintf(stderr, "Failed to populate tuple\n");
        tuple_free(&t);
        return EXIT_FAILURE;
    }

    printf("Original tuple: ");
    tuple_print(&t);

    if (tuple_remove_type(&t, TYPE_STRING) != 0) {
        fprintf(stderr, "Failed to remove elements\n");
        tuple_free(&t);
        return EXIT_FAILURE;
    }

    printf("After removing strings: ");
    tuple_print(&t);

    if (tuple_remove_type(&t, TYPE_FLOAT) != 0) {
        fprintf(stderr, "Failed to remove elements\n");
        tuple_free(&t);
        return EXIT_FAILURE;
    }

    printf("After removing floats: ");
    tuple_print(&t);

    tuple_free(&t);
    return EXIT_SUCCESS;
}