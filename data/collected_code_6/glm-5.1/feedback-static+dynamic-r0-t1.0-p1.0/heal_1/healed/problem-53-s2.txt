#include <stdio.h>
#include <stdbool.h>

bool are_first_and_last_equal(const char *str, size_t max_len) {
    if (str == NULL) {
        return false;
    }

    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }

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

    printf("%d\n", are_first_and_last_equal(test1, 1024));
    printf("%d\n", are_first_and_last_equal(test2, 1024));
    printf("%d\n", are_first_and_last_equal(test3, 1024));
    printf("%d\n", are_first_and_last_equal(test4, 1024));
    printf("%d\n", are_first_and_last_equal(test5, 1024));

    return 0;
}