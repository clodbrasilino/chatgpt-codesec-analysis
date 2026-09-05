#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

typedef struct {
    int success;
    union {
        float f;
        int error_code;
    } value;
} Tuple;

Tuple str_to_float_tuple(const char *str) {
    Tuple t;
    char *endptr;
    if (str == NULL || *str == '\0') {
        t.success = 0;
        t.value.error_code = 1;
        return t;
    }
    t.value.f = strtof(str, &endptr);
    /* Possible weaknesses found:
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'ERANGE' undeclared (first use in this function)
     */
    if (errno == ERANGE) {
        t.success = 0;
        t.value.error_code = 2;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'errno'
         */
        errno = 0;
        return t;
    }
    if (*endptr != '\0') {
        t.success = 0;
        t.value.error_code = 3;
        return t;
    }
    t.success = 1;
    return t;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <float_string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    Tuple t = str_to_float_tuple(argv[1]);
    if (t.success == 1) {
        printf("%f\n", t.value.f);
    } else {
        printf("Error: %d\n", t.value.error_code);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}