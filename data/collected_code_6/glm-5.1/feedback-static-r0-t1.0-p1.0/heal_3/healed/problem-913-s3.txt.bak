#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ends_with_number(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }

    size_t len = strlen(str);
    const char *end = str + len - 1;

    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }

    if (end < str) {
        return 0;
    }

    if (isdigit((unsigned char)*end)) {
        while (end >= str && isdigit((unsigned char)*end)) {
            end--;
        }
        if (end >= str && isalpha((unsigned char)*end)) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test1 = "abc123";
    const char *test2 = "abc";
    const char *test3 = "123";
    const char *test4 = "abc123 ";
    const char *test5 = "";
    const char *test6 = NULL;
    const char *test7 = "abc!123";
    const char *test8 = "abc 123";

    printf("%s: %d\n", test1 ? test1 : "(null)", ends_with_number(test1));
    printf("%s: %d\n", test2 ? test2 : "(null)", ends_with_number(test2));
    printf("%s: %d\n", test3 ? test3 : "(null)", ends_with_number(test3));
    printf("%s: %d\n", test4 ? test4 : "(null)", ends_with_number(test4));
    printf("%s: %d\n", test5 ? test5 : "(null)", ends_with_number(test5));
    printf("%s: %d\n", test6 ? test6 : "(null)", ends_with_number(test6));
    printf("%s: %d\n", test7 ? test7 : "(null)", ends_with_number(test7));
    printf("%s: %d\n", test8 ? test8 : "(null)", ends_with_number(test8));

    return 0;
}