#include <stdio.h>
#include <string.h>

void removeFirstAndLastOccurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }

    int first = -1;
    int last = -1;
    int len = 0;

    while (str[len] != '\0') {
        if (str[len] == ch) {
            if (first == -1) {
                first = len;
            }
            last = len;
        }
        len++;
    }

    if (first != -1) {
        if (first == last) {
            for (int i = first; i < len; i++) {
                str[i] = str[i + 1];
            }
        } else {
            for (int i = last; i < len; i++) {
                str[i] = str[i + 1];
            }
            len--; 
            for (int i = first; i < len; i++) {
                str[i] = str[i + 1];
            }
        }
    }
}

int main(void) {
    char str1[] = "hello world";
    char ch1 = 'l';
    removeFirstAndLastOccurrence(str1, ch1);
    printf("%s\n", str1);

    char str2[] = "programming";
    char ch2 = 'g';
    removeFirstAndLastOccurrence(str2, ch2);
    printf("%s\n", str2);

    char str3[] = "test";
    char ch3 = 't';
    removeFirstAndLastOccurrence(str3, ch3);
    printf("%s\n", str3);

    char str4[] = "abc";
    char ch4 = 'z';
    removeFirstAndLastOccurrence(str4, ch4);
    printf("%s\n", str4);

    return 0;
}