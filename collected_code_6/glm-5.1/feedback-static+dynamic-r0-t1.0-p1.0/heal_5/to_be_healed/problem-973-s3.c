#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *left_rotate(char *str, size_t n) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    size_t shift = n % len;
    /* Possible weaknesses found:
     *  Assuming that condition 'shift==0' is not redundant
     */
    if (shift == 0) {
        return str;
    }

    char *temp = (char *)malloc(len + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return NULL;
    }

    if (len - shift > 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'memcpy_s'; did you mean 'memcpy'? [-Wimplicit-function-declaration]
         *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  did you mean 'memcpy'?
         */
        errno_t err = memcpy_s(temp, len + 1, str + shift, len - shift);
        if (err != 0) {
            free(temp);
            return NULL;
        }
    }

    /* Possible weaknesses found:
     *  Condition 'shift>0' is always true
     *  Condition 'shift>0' is always true [knownConditionTrueFalse]
     */
    if (shift > 0) {
        /* Possible weaknesses found:
         *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        errno_t err = memcpy_s(temp + len - shift, shift + 1, str, shift);
        if (err != 0) {
            free(temp);
            return NULL;
        }
    }

    temp[len] = '\0';

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    errno_t err = memcpy_s(str, len + 1, temp, len);
    if (err != 0) {
        free(temp);
        return NULL;
    }
    str[len] = '\0';

    free(temp);

    return str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <rotate_amount>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(argv[1]);
    char *input = (char *)malloc(input_len + 1);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  call to undeclared function 'memcpy_s'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    errno_t err = memcpy_s(input, input_len + 1, argv[1], input_len + 1);
    if (err != 0) {
        fprintf(stderr, "Memory copy failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val < 0) {
        /* Possible weaknesses found:
         *  'memcpy' declared here
         */
        fprintf(stderr, "Rotate amount must be a non-negative integer\n");
        free(input);
        return EXIT_FAILURE;
    }

    size_t n = (size_t)val;

    char *result = left_rotate(input, n);
    if (result == NULL) {
        fprintf(stderr, "Rotation failed\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("%s\n", result);

    free(input);

    return EXIT_SUCCESS;
}