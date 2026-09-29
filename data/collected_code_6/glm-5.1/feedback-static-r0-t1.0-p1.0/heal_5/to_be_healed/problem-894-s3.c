#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
    errno = 0;
    t.value.f = strtof(str, &endptr);
    if (errno == ERANGE) {
        t.success = 0;
        t.value.error_code = 2;
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
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[static 2]) {
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