#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  */

char *camel_to_snake(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (int i = 0, len = strlen(str); i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
            memmove(&str[i + 1], &str[i], len - i);
            str[i] = '_';
            len++;
        }
    }
    return str;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    printf("Enter a camel case string: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    scanf("%255s", str);
    camel_to_snake(str);
    printf("Snake case: %s\n", str);
    return 0;
}