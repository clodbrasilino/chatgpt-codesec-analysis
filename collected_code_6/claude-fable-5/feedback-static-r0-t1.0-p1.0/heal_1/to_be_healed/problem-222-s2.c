#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR
} ElementType;

typedef struct {
    ElementType type;
    union {
        int i_val;
        double d_val;
        /* Possible weaknesses found:
         *  union member 'Anonymous0::s_val' is never used. [unusedStructMember]
         */
        char *s_val;
        char c_val;
    } data;
} Element;

typedef struct {
    Element *elements;
    size_t count;
} Tuple;

static bool check_same_type(const Tuple *tuple, bool *result)
{
    size_t idx;

    if ((tuple == NULL) || (result == NULL)) {
        return false;
    }

    if ((tuple->count > 0U) && (tuple->elements == NULL)) {
        return false;
    }

    *result = true;

    if (tuple->count <= 1U) {
        return true;
    }

    for (idx = 1U; idx < tuple->count; idx++) {
        if (tuple->elements[idx].type != tuple->elements[0U].type) {
            *result = false;
            break;
        }
    }

    return true;
}

static const char *type_name(ElementType type)
{
    const char *name;

    switch (type) {
    case TYPE_INT:
        name = "int";
        break;
    case TYPE_DOUBLE:
        name = "double";
        break;
    case TYPE_STRING:
        name = "string";
        break;
    case TYPE_CHAR:
        name = "char";
        break;
    default:
        name = "unknown";
        break;
    }

    return name;
}

static void print_tuple(const Tuple *tuple)
{
    size_t idx;

    if ((tuple == NULL) || ((tuple->count > 0U) && (tuple->elements == NULL))) {
        (void)printf("(invalid tuple)\n");
        return;
    }

    (void)printf("(");
    for (idx = 0U; idx < tuple->count; idx++) {
        (void)printf("%s", type_name(tuple->elements[idx].type));
        if (idx < (tuple->count - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf(")\n");
}

int main(void)
{
    bool same;
    Element homogeneous[3];
    Element mixed[3];
    Tuple tuple1;
    Tuple tuple2;
    Tuple empty_tuple;

    homogeneous[0].type = TYPE_INT;
    homogeneous[0].data.i_val = 10;
    homogeneous[1].type = TYPE_INT;
    homogeneous[1].data.i_val = 20;
    homogeneous[2].type = TYPE_INT;
    homogeneous[2].data.i_val = 30;

    mixed[0].type = TYPE_INT;
    mixed[0].data.i_val = 1;
    mixed[1].type = TYPE_DOUBLE;
    mixed[1].data.d_val = 2.5;
    mixed[2].type = TYPE_CHAR;
    mixed[2].data.c_val = 'a';

    tuple1.elements = homogeneous;
    tuple1.count = 3U;

    tuple2.elements = mixed;
    tuple2.count = 3U;

    empty_tuple.elements = NULL;
    empty_tuple.count = 0U;

    print_tuple(&tuple1);
    if (check_same_type(&tuple1, &same)) {
        (void)printf("All elements same type: %s\n\n", same ? "true" : "false");
    } else {
        (void)fprintf(stderr, "Error: invalid tuple input\n");
        return EXIT_FAILURE;
    }

    print_tuple(&tuple2);
    if (check_same_type(&tuple2, &same)) {
        (void)printf("All elements same type: %s\n\n", same ? "true" : "false");
    } else {
        (void)fprintf(stderr, "Error: invalid tuple input\n");
        return EXIT_FAILURE;
    }

    print_tuple(&empty_tuple);
    if (check_same_type(&empty_tuple, &same)) {
        (void)printf("All elements same type: %s\n", same ? "true" : "false");
    } else {
        (void)fprintf(stderr, "Error: invalid tuple input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}