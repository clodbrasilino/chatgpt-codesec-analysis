#include <string.h>
#include <stdio.h>
#include <stddef.h>
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
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i = (int)(strlen(s)) - 1;

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