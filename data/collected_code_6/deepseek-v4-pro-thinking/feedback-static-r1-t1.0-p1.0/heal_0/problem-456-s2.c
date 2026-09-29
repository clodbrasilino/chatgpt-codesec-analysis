#include <stddef.h>
#include <stdio.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    if (len < 2) {
        return;
    }

    char *left = str;
    char *right = str + len - 1;

    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

void reverse_strings(char *strings[], size_t count) {
    if (strings == NULL || count == 0) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    char s0[] = "hello";
    char s1[] = "world";
    char s2[] = "C";
    char s3[] = "";
    char *strings[] = { s0, s1, s2, s3 };
    size_t count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}