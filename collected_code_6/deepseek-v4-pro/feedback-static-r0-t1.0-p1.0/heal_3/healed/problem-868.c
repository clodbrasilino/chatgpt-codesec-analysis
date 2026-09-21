#include <string.h>
#include <stdio.h>
#include <stddef.h>

int lengthOfLastWord(const char *s) {
    int length = 0;
    int i;
    size_t len;

    if (s == NULL || *s == '\0') {
        return 0;
    }

    len = strlen(s);
    if (len == 0) {
        return 0;
    }

    i = (int)len - 1;

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