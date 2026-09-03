#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  */

char *camel_to_snake(char *str) {
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
    char str[256];
    printf("Enter a camel case string: ");
    scanf("%255s", str);
    camel_to_snake(str);
    printf("Snake case: %s\n", str);
    return 0;
}