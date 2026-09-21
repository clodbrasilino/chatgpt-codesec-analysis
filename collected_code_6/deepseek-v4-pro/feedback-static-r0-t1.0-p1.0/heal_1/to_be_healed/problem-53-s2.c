#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool first_last_equal(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    return str[0] == str[len - 1];
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;
    const char *test6 = "racecar";

    printf("%d\n", first_last_equal(test1));
    printf("%d\n", first_last_equal(test2));
    printf("%d\n", first_last_equal(test3));
    printf("%d\n", first_last_equal(test4));
    printf("%d\n", first_last_equal(test5));
    printf("%d\n", first_last_equal(test6));

    return 0;
}