#include <string.h>
#include <stdio.h>
#include <stddef.h>

int lengthOfLastWord(const char *s) {
    int length = 0;
    int i;

    if (s == NULL) {
        return 0;
    }

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            if (s[i + 1] != '\0' && s[i + 1] != ' ') {
                length = 0;
            }
        } else {
            length++;
        }
    }

    return length;
}

int main(void) {
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    const char *test4 = "   ";
    const char *test5 = "a";

    printf("%d\n", lengthOfLastWord(test1));
    printf("%d\n", lengthOfLastWord(test2));
    printf("%d\n", lengthOfLastWord(test3));
    printf("%d\n", lengthOfLastWord(test4));
    printf("%d\n", lengthOfLastWord(test5));

    return 0;
}