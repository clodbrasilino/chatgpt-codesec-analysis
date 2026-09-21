#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  */

int lengthOfLastWord(const char *s) {
    int length = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const char *p = s + strlen(s) - 1;
    while (p >= s && isspace((unsigned char)*p)) p--;
    while (p >= s && !isspace((unsigned char)*p)) {
        length++;
        p--;
    }
    return length;
}

int main() {
    const char *str0 = "Hello World      ";
    const char *str1 = "   fly me   to   the moon  ";
    const char *str2 = "luffy is still joyboy";
    
    printf("Length of the last word: %d\n", lengthOfLastWord(str0));
    printf("Length of the last word: %d\n", lengthOfLastWord(str1));
    printf("Length of the last word: %d\n", lengthOfLastWord(str2));
    
    return 0;
}