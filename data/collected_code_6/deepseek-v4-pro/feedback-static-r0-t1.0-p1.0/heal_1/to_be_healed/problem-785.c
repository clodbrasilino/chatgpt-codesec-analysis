#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int parse_tuple_string(const char *tuple_str, int **tuple, size_t *tuple_size) {
    if (tuple_str == NULL || tuple == NULL || tuple_size == NULL) {
        errno = EINVAL;
        return -1;
    }

    *tuple = NULL;
    *tuple_size = 0;

    const char *p = tuple_str;

    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p != '(') {
        errno = EINVAL;
        return -1;
    }
    p++;

    size_t capacity = 0;
    size_t count = 0;
    int *values = NULL;

    while (1) {
        while (isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == ')') {
            p++;
            break;
        }

        if (*p == '\0') {
            free(values);
            errno = EINVAL;
            return -1;
        }

        errno = 0;
        char *endptr = NULL;
        long val = strtol(p, &endptr, 10);

        if (errno != 0 || endptr == p) {
            free(values);
            errno = EINVAL;
            return -1;
        }

        /* Possible weaknesses found:
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MIN' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         */
        if (val < INT_MIN || val > INT_MAX) {
            free(values);
            errno = ERANGE;
            return -1;
        }

        if (count == capacity) {
            size_t new_capacity = (capacity == 0) ? 4 : capacity * 2;
            int *new_values = realloc(values, new_capacity * sizeof(int));
            if (new_values == NULL) {
                free(values);
                errno = ENOMEM;
                return -1;
            }
            values = new_values;
            capacity = new_capacity;
        }

        values[count] = (int)val;
        count++;

        p = endptr;

        while (isspace((unsigned char)*p)) {
            p++;
        }

        if (*p == ',') {
            p++;
            continue;
        }

        if (*p == ')') {
            p++;
            break;
        }

        free(values);
        errno = EINVAL;
        return -1;
    }

    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p != '\0') {
        free(values);
        errno = EINVAL;
        return -1;
    }

    *tuple = values;
    *tuple_size = count;
    return 0;
}

int main(void) {
    const char *test_cases[] = {
        "(1, 2, 3)",
        "(42)",
        "()",
        "(10, -5, 0, 2147483647, -2147483648)",
        "invalid",
        "(1, 2",
        "(1, 2,)",
        "(1, 2, 3)x",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        int *tuple = NULL;
        size_t size = 0;
        int result = parse_tuple_string(test_cases[i], &tuple, &size);

        printf("Input: '%s'\n", test_cases[i]);
        if (result == 0) {
            printf("Parsed %zu elements: (", size);
            for (size_t j = 0; j < size; j++) {
                if (j > 0) {
                    printf(", ");
                }
                printf("%d", tuple[j]);
            }
            printf(")\n");
            free(tuple);
        } else {
            printf("Error parsing tuple: %s\n", strerror(errno));
        }
        printf("\n");
    }

    return 0;
}