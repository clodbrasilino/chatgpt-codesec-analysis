#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    int len = strlen(str);
    int first, last;
    first = last = -1;

    for (int i = 0; i < len; ++i) {
        if (str[i] == ch && first == -1) {
            first = i;
        }
        if (str[len - i - 1] == ch) {
            last = len - i - 1;
        }
    }

    if (first != -1) {
        memmove(str + first, str + first + 1, (len - first - 1) * sizeof(char));
        --len;
    }

    if (last != -1 && last > first) {
        memmove(str + last, str + last + 1, (len - last - 1) * sizeof(char));
    }

    str[(first != -1 ? (last != -1 ? last : len) : len)] = '\0';
}

int main() {
    char str[] = "hello world";
    char ch = 'o';

    printf("Original string: %s\n", str);
    remove_first_last_occurrence(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}