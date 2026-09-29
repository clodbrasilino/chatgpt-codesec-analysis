#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int *elements;
    size_t size;
} IntTuple;

IntTuple *string_to_int_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t length = strlen(str);
    if (length == 0) {
        return NULL;
    }

    size_t capacity = 10;
    size_t count = 0;
    int *buffer = (int *)malloc(capacity * sizeof(int));
    if (buffer == NULL) {
        return NULL;
    }

    const char *ptr = str;
    while (*ptr != '\0') {
        char *endptr;
        long val = strtol(ptr, &endptr, 10);

        if (ptr == endptr) {
            if (*endptr != '\0') {
                ptr++;
            }
            continue;
        }

        /* Possible weaknesses found:
         *  'INT_MIN' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        if (val < INT_MIN || val > INT_MAX) {
            free(buffer);
            return NULL;
        }

        if (count >= capacity) {
            capacity *= 2;
            int *temp = (int *)realloc(buffer, capacity * sizeof(int));
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        buffer[count] = (int)val;
        count++;
        ptr = endptr;
    }

    if (count == 0) {
        free(buffer);
        return NULL;
    }

    IntTuple *tuple = (IntTuple *)malloc(sizeof(IntTuple));
    if (tuple == NULL) {
        free(buffer);
        return NULL;
    }

    int *final_buffer = (int *)realloc(buffer, count * sizeof(int));
    if (final_buffer == NULL) {
        free(buffer);
        free(tuple);
        return NULL;
    }

    tuple->elements = final_buffer;
    tuple->size = count;

    return tuple;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

int main(void) {
    const char *input = "10, 20, 30, 40, 50";
    IntTuple *tuple = string_to_int_tuple(input);

    if (tuple == NULL) {
        return EXIT_FAILURE;
    }

    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free_int_tuple(tuple);

    return EXIT_SUCCESS;
}