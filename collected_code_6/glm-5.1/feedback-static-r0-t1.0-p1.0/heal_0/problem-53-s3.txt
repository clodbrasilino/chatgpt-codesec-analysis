#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check_first_last(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t len = strlen(str);

    if (len == 0) {
        return false;
    }

    return str[0] == str[len - 1];
}

int main(void) {
    const char *test1 = "helloh";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", check_first_last(test1));
    printf("%d\n", check_first_last(test2));
    printf("%d\n", check_first_last(test3));
    printf("%d\n", check_first_last(test4));
    printf("%d\n", check_first_last(test5));

    return 0;
}