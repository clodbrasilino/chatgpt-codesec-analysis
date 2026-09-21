#include <stdio.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int check_string(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int has_letter = 0;
    int has_number = 0;

    for (const char *p = str; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) {
            has_letter = 1;
        } else if (isdigit((unsigned char)*p)) {
            has_number = 1;
        }

        if (has_letter && has_number) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test1 = "12345";
    const char *test2 = "abcde";
    const char *test3 = "a1b2c";
    const char *test4 = "";
    const char *test5 = "!@#1a";

    printf("%d\n", check_string(test1));
    printf("%d\n", check_string(test2));
    printf("%d\n", check_string(test3));
    printf("%d\n", check_string(test4));
    printf("%d\n", check_string(test5));

    return 0;
}