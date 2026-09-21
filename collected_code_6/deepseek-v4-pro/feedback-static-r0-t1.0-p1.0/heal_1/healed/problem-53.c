#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool first_last_equal(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (*str == '\0') {
        return false;
    }

    const char *last = str;
    while (*last != '\0') {
        last++;
    }
    last--;

    return *str == *last;
}

int main(void) {
    const char *test1 = "abca";
    const char *test2 = "abc";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", first_last_equal(test1));
    printf("%d\n", first_last_equal(test2));
    printf("%d\n", first_last_equal(test3));
    printf("%d\n", first_last_equal(test4));
    printf("%d\n", first_last_equal(test5));

    return 0;
}