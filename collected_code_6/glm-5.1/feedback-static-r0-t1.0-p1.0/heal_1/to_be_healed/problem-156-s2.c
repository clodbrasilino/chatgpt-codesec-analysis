#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int *convert_string_tuple_to_int(const char **str_tuple, size_t size) {
    if (str_tuple == NULL || size == 0) {
        return NULL;
    }

    int *int_tuple = (int *)malloc(size * sizeof(int));
    if (int_tuple == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        if (str_tuple[i] == NULL) {
            free(int_tuple);
            return NULL;
        }

        char *endptr;
        long val = strtol(str_tuple[i], &endptr, 10);

        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MIN' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         *  'INT_MAX' undeclared (first use in this function)
         */
        if (endptr == str_tuple[i] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(int_tuple);
            return NULL;
        }

        int_tuple[i] = (int)val;
    }

    return int_tuple;
}

int main(void) {
    const char *str_tuple[] = {"10", "20", "30", "40"};
    size_t size = sizeof(str_tuple) / sizeof(str_tuple[0]);

    int *int_tuple = convert_string_tuple_to_int(str_tuple, size);
    if (int_tuple == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++) {
        printf("%d ", int_tuple[i]);
    }
    printf("\n");

    free(int_tuple);

    return EXIT_SUCCESS;
}