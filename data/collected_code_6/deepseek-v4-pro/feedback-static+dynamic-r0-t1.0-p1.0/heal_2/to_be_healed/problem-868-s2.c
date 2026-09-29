#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 8, got <no output>
  *  test case 1 failed: expected 3, got <no output>
  */

int lengthOfLastWord(const char *s) {
    int length = 0;
    int i;
    size_t len;
    
    if (s == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(s);
    if (len == 0) {
        return 0;
    }
    
    i = (int)len - 1;
    
    while (i >= 0 && isspace((unsigned char)s[i])) {
        i--;
    }
    
    while (i >= 0 && !isspace((unsigned char)s[i])) {
        length++;
        i--;
    }
    
    return length;
}

int main(void) {
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    const char *test4 = "single";
    const char *test5 = "  ";
    const char *test6 = "";
    
    printf("Test 1: %d\n", lengthOfLastWord(test1));
    printf("Test 2: %d\n", lengthOfLastWord(test2));
    printf("Test 3: %d\n", lengthOfLastWord(test3));
    printf("Test 4: %d\n", lengthOfLastWord(test4));
    printf("Test 5: %d\n", lengthOfLastWord(test5));
    printf("Test 6: %d\n", lengthOfLastWord(test6));
    
    return 0;
}