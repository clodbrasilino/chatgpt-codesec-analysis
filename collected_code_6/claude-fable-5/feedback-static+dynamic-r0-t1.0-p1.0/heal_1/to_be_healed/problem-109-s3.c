#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_odd_rotations(const char *str)
{
    size_t len;
    size_t i;
    int count;

    if (str == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return -1;
    }

    count = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '1') {
            count++;
        } else if (str[i] != '0') {
            return -1;
        }
    }

    return count;
}

int main(void)
{
    const char *test1 = "011001";
    const char *test2 = "11011";
    const char *test3 = "0000";
    int result;

    result = count_odd_rotations(test1);
    if (result < 0) {
        fprintf(stderr, "Invalid input: %s\n", test1);
        return EXIT_FAILURE;
    }
    printf("Odd rotations of %s: %d\n", test1, result);

    result = count_odd_rotations(test2);
    if (result < 0) {
        fprintf(stderr, "Invalid input: %s\n", test2);
        return EXIT_FAILURE;
    }
    printf("Odd rotations of %s: %d\n", test2, result);

    result = count_odd_rotations(test3);
    if (result < 0) {
        fprintf(stderr, "Invalid input: %s\n", test3);
        return EXIT_FAILURE;
    }
    printf("Odd rotations of %s: %d\n", test3, result);

    return EXIT_SUCCESS;
}