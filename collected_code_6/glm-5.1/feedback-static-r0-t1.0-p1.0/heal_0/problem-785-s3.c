#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int *elements;
    size_t count;
} IntTuple;

IntTuple parse_tuple(const char *str) {
    IntTuple result = {NULL, 0};
    const char *p = str;
    size_t capacity = 0;

    if (p == NULL || *p != '(') {
        return result;
    }
    p++;

    while (*p != '\0') {
        while (*p == ' ' || *p == ',') {
            p++;
        }

        if (*p == ')') {
            break;
        }

        if (*p == '\0') {
            free(result.elements);
            result.elements = NULL;
            result.count = 0;
            return result;
        }

        char *end;
        errno = 0;
        long val = strtol(p, &end, 10);

        if (p == end || errno == ERANGE || val < INT_MIN || val > INT_MAX) {
            free(result.elements);
            result.elements = NULL;
            result.count = 0;
            return result;
        }

        if (result.count >= capacity) {
            size_t new_capacity = (capacity == 0) ? 4 : capacity * 2;
            int *new_elements = realloc(result.elements, new_capacity * sizeof(int));
            if (new_elements == NULL) {
                free(result.elements);
                result.elements = NULL;
                result.count = 0;
                return result;
            }
            result.elements = new_elements;
            capacity = new_capacity;
        }

        result.elements[result.count++] = (int)val;
        p = end;
    }

    int *final_elements = realloc(result.elements, result.count * sizeof(int));
    if (final_elements != NULL || result.count == 0) {
        result.elements = final_elements;
    }

    return result;
}

int main(void) {
    const char *str = "(10, -20, 30, -40)";
    IntTuple tuple = parse_tuple(str);

    if (tuple.elements != NULL) {
        printf("(");
        for (size_t i = 0; i < tuple.count; ++i) {
            printf("%d", tuple.elements[i]);
            if (i < tuple.count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    } else {
        printf("Parse error\n");
    }

    free(tuple.elements);
    return 0;
}