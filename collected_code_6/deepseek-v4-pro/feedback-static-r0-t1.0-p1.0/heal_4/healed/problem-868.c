#include <string.h>
#include <stdio.h>
#include <stddef.h>

int lengthOfLastWord(const char *s) {
    int length = 0;
    int i;
    const char *ptr;

    if (s == NULL) {
        return 0;
    }

    ptr = s;
    while (*ptr != '\0') {
        ptr++;
    }

    if (ptr == s) {
        return 0;
    }

    i = (int)(ptr - s) - 1;

    while (i >= 0 && s[i] == ' ') {
        i--;
    }

    while (i >= 0 && s[i] != ' ') {
        length++;
        i--;
    }

    return length;
}

int main(void) {
    const char *test_strings[] = {
        "Hello World",
        "   fly me   to   the moon  ",
        "luffy is still joyboy",
        "single",
        "   ",
        ""
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            printf("\"%s\" -> %d\n", test_strings[i], lengthOfLastWord(test_strings[i]));
        }
    }

    return 0;
}