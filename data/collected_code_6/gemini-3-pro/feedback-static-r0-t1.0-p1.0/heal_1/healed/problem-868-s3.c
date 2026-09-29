#include <stdio.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int final_length = 0;
    int current_length = 0;

    while (*s != '\0') {
        if (*s != ' ') {
            current_length++;
            final_length = current_length;
        } else {
            current_length = 0;
        }
        s++;
    }

    return final_length;
}

int main(void) {
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    const char *test4 = "";
    const char *test5 = NULL;

    printf("%d\n", lengthOfLastWord(test1));
    printf("%d\n", lengthOfLastWord(test2));
    printf("%d\n", lengthOfLastWord(test3));
    printf("%d\n", lengthOfLastWord(test4));
    printf("%d\n", lengthOfLastWord(test5));

    return 0;
}