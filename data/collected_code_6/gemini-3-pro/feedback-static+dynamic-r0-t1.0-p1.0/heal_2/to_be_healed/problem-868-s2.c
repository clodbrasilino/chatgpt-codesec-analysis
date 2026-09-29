#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  */

int lengthOfLastWord(const char *s) {
    if (s == NULL) {
        return 0;
    }

    int length = 0;
    int current_length = 0;

    while (*s != '\0') {
        if (*s == ' ') {
            if (current_length > 0) {
                length = current_length;
            }
            current_length = 0;
        } else {
            current_length++;
        }
        s++;
    }

    return current_length > 0 ? current_length : length;
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