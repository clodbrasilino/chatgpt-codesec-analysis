#include <stdio.h>
#include <string.h>

void removeFirstAndLastOccurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t first = len;
    size_t last = len;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (first == len) {
                first = i;
            }
            last = i;
        }
    }

    if (first == len) {
        return;
    }

    if (first == last) {
        memmove(str + first, str + first + 1, len - first);
    } else {
        memmove(str + last, str + last + 1, len - last);
        memmove(str + first, str + first + 1, last - first);
    }
}

int main(void) {
    char str[100];
    char ch;
    int c;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    printf("Enter a character to remove: ");
    c = getchar();
    if (c == EOF || c == '\n') {
        return 1;
    }
    ch = (char)c;

    removeFirstAndLastOccurrence(str, ch);

    printf("Result: %s\n", str);

    return 0;
}