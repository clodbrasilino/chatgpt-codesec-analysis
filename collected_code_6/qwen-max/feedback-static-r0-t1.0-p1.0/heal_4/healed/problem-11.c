#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    size_t len = 0;
    while (str[len] && str[len] != ch) ++len;
    if (str[len]) --len;

    int first = -1, last = -1;

    for (size_t i = 0; i <= len; ++i) {
        if (str[i] == ch && first == -1) {
            first = i;
        }
        if (str[len - i] == ch && (last == -1 || len - i > last)) {
            last = len - i;
        }
    }

    if (first != -1 && first <= len) {
        memmove(str + first, str + first + 1, len - first);
        --len;
    }

    if (last != -1 && (last > first || first == -1) && last <= len) {
        memmove(str + last, str + last + 1, len - last);
        --len;
    }

    str[++len] = '\0';
}

int main() {
    char str[] = "hello world";
    char ch = 'o';

    printf("Original string: %s\n", str);
    remove_first_last_occurrence(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}