#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int starts_with_number(const char *str, int number) {
    char *num_str = NULL;
    int ret = -1;

    if (asprintf(&num_str, "%d", number) > 0) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(num_str);
        if (strncmp(str, num_str, len) == 0) {
            ret = 0;
        }
        free(num_str);
    }

    return ret;
}

int main() {
    const char *test_str = "1234_start";
    int test_num = 1234;
    if (starts_with_number(test_str, test_num) == 0) {
        printf("The string starts with the number %d.\n", test_num);
    } else {
        printf("The string does not start with the number %d.\n", test_num);
    }
    return 0;
}