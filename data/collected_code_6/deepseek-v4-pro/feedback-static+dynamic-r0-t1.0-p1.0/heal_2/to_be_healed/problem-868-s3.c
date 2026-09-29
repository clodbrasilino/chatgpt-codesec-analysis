#include <string.h>
#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  */

int lengthOfLastWord(const char *s) {
    int length = 0;
    
    if (s == NULL) {
        return 0;
    }

    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    i--;

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