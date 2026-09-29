#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    free(tuple->values);
    tuple->values = NULL;
    tuple->length = 0;
}

Tuple string_to_tuple(const char *str) {
    Tuple result = {NULL, 0};
    const char *p = str;
    int *data = NULL;
    size_t count = 0;
    size_t capacity = 0;

    if (str == NULL) {
        return result;
    }

    while (*p != '\0') {
        while (isspace((unsigned char)*p) || *p == ',' || *p == '(' || *p == ')') {
            p++;
        }

        if (*p == '\0') {
            break;
        }

        errno = 0;
        char *end = NULL;
        long value = strtol(p, &end, 10);

        if (end == p || errno == ERANGE || value > INT_MAX || value < INT_MIN) {
            free(data);
            result.values = NULL;
            result.length = 0;
            return result;
        }

        if (count == capacity) {
            size_t new_capacity;

            if (capacity == 0) {
                new_capacity = 4;
            } else if (capacity > (size_t)-1 / 2) {
                free(data);
                result.values = NULL;
                result.length = 0;
                return result;
            } else {
                new_capacity = capacity * 2;
            }

            int *new_data = realloc(data, new_capacity * sizeof(*data));
            if (new_data == NULL) {
                free(data);
                result.values = NULL;
                result.length = 0;
                return result;
            }

            data = new_data;
            capacity = new_capacity;
        }

        data[count] = (int)value;
        count++;
        p = end;
    }

    result.values = data;
    result.length = count;
    return result;
}

int main(void) {
    Tuple tuple = string_to_tuple("1, 2, 3, 4, 5");

    printf("(");
    for (size_t i = 0; i < tuple.length; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", tuple.values[i]);
    }
    printf(")\n");

    tuple_free(&tuple);
    return 0;
}