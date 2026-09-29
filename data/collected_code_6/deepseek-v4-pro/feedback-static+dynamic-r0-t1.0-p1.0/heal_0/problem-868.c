#include <string.h>
#include <stdio.h>

int lengthOfLastWord(const char *s) {
    int length = 0;
    int i = strlen(s) - 1;

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
        printf("\"%s\" -> %d\n", test_strings[i], lengthOfLastWord(test_strings[i]));
    }

    return 0;
}