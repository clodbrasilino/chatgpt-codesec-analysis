#include <stdio.h>

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    int current_length = 0;

    while (*s != '\0') {
        if (*s == ' ') {
            current_length = 0;
        } else {
            current_length++;
            length = current_length;
        }
        s++;
    }

    return length;
}

int main(void) {
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    
    printf("%d\n", lengthOfLastWord(test1));
    printf("%d\n", lengthOfLastWord(test2));
    printf("%d\n", lengthOfLastWord(test3));
    
    return 0;
}