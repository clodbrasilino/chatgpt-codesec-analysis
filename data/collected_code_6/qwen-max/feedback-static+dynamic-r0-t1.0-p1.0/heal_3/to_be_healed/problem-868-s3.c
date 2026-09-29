#include <stdio.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  */

int lengthOfLastWord(const char *s) {
    int len = 0;
    int i = 0;

    while (s[i] != '\0') {
        if (isspace(s[i])) {
            len = 0;
        } else {
            len++;
        }
        i++;
    }

    return len;
}

int main() {
    const char *s = "Hello, World!";
    int result = lengthOfLastWord(s);
    printf("Length of last word: %d\n", result);
    return 0;
}