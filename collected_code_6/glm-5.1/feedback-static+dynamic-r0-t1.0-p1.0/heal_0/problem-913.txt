#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ends_with_number(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    return isdigit((unsigned char)str[len - 1]);
}

int main(void) {
    const char *test1 = "hello123";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = NULL;
    const char *test5 = "test5";

    printf("ends_with_number(\"%s\"): %d\n", test1, ends_with_number(test1));
    printf("ends_with_number(\"%s\"): %d\n", test2, ends_with_number(test2));
    printf("ends_with_number(\"%s\"): %d\n", test3, ends_with_number(test3));
    printf("ends_with_number(NULL): %d\n", ends_with_number(test4));
    printf("ends_with_number(\"%s\"): %d\n", test5, ends_with_number(test5));

    return 0;
}