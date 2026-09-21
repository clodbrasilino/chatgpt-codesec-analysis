#include <stdio.h>
#include <stdbool.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return true;
    }

    char first = str[0];
    size_t i = 1;
    
    while (str[i] != '\0') {
        if (str[i] != first) {
            return false;
        }
        i++;
    }

    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abaa";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("%d\n", are_all_chars_same(test1));
    printf("%d\n", are_all_chars_same(test2));
    printf("%d\n", are_all_chars_same(test3));
    printf("%d\n", are_all_chars_same(test4));

    return 0;
}