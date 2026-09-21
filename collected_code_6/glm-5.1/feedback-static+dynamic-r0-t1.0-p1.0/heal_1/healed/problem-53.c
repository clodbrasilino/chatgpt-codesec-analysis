#include <stdio.h>
#include <string.h>

int check_first_last(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }
    return str[0] == str[len - 1];
}

int main(void) {
    const char *test1 = "helloh";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", check_first_last(test1, 6));
    printf("%d\n", check_first_last(test2, 5));
    printf("%d\n", check_first_last(test3, 1));
    printf("%d\n", check_first_last(test4, 0));
    printf("%d\n", check_first_last(test5, 0));

    return 0;
}