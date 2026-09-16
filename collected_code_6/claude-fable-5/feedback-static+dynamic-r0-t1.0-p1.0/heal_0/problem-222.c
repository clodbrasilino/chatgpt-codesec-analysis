#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_CHAR
} DataType;

typedef struct {
    DataType type;
    union {
        int i;
        double d;
        const char *s;
        char c;
    } value;
} Element;

static bool all_same_type(const Element *tuple, size_t count)
{
    size_t idx;

    if (tuple == NULL) {
        return false;
    }

    if (count == 0U) {
        return true;
    }

    for (idx = 1U; idx < count; idx++) {
        if (tuple[idx].type != tuple[0].type) {
            return false;
        }
    }

    return true;
}

static const char *type_name(DataType type)
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

static void print_result(const char *label, const Element *tuple, size_t count)
{
    if (label == NULL) {
        return;
    }

    if (all_same_type(tuple, count)) {
        if (count > 0U && tuple != NULL) {
            if (printf("%s: all elements have the same type (%s)\n",
                       label, type_name(tuple[0].type)) < 0) {
                return;
            }
        } else {
            if (printf("%s: tuple is empty, trivially same type\n",
                       label) < 0) {
                return;
            }
        }
    } else {
        if (printf("%s: elements have different types\n", label) < 0) {
            return;
        }
    }
}

int main(void)
{
    Element tuple1[3];
    Element tuple2[3];
    Element tuple3[2];

    tuple1[0].type = TYPE_INT;
    tuple1[0].value.i = 10;
    tuple1[1].type = TYPE_INT;
    tuple1[1].value.i = 20;
    tuple1[2].type = TYPE_INT;
    tuple1[2].value.i = 30;

    tuple2[0].type = TYPE_INT;
    tuple2[0].value.i = 1;
    tuple2[1].type = TYPE_DOUBLE;
    tuple2[1].value.d = 2.5;
    tuple2[2].type = TYPE_STRING;
    tuple2[2].value.s = "hello";

    tuple3[0].type = TYPE_CHAR;
    tuple3[0].value.c = 'a';
    tuple3[1].type = TYPE_CHAR;
    tuple3[1].value.c = 'b';

    print_result("Tuple 1", tuple1, sizeof(tuple1) / sizeof(tuple1[0]));
    print_result("Tuple 2", tuple2, sizeof(tuple2) / sizeof(tuple2[0]));
    print_result("Tuple 3", tuple3, sizeof(tuple3) / sizeof(tuple3[0]));
    print_result("Empty tuple", tuple1, 0U);
    print_result("Null tuple", NULL, 3U);

    return 0;
}