#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool all_chars_unique(const char *str)
{
    bool seen[UCHAR_MAX + 1] = { false };
    size_t i;

    if (str == NULL) {
        return false;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return false;
        }
        seen[c] = true;
    }

    return true;
}

int main(void)
{
    const char *test1 = "abcdefg";
    const char *test2 = "hello";
    const char *test3 = "";

    if (all_chars_unique(test1)) {
        printf("\"%s\": all characters are unique\n", test1);
    } else {
        printf("\"%s\": contains duplicate characters\n", test1);
    }

    if (all_chars_unique(test2)) {
        printf("\"%s\": all characters are unique\n", test2);
    } else {
        printf("\"%s\": contains duplicate characters\n", test2);
    }

    if (all_chars_unique(test3)) {
        printf("\"%s\": all characters are unique\n", test3);
    } else {
        printf("\"%s\": contains duplicate characters\n", test3);
    }

    return 0;
}