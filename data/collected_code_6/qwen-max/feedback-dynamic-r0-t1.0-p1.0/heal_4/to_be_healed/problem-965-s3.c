#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  */

char *camel_to_snake(char *str) {
    int len = strlen(str);
    char *new_str = str;
    for (int i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i])) {
            memmove(&str[i + 1], &str[i], len - i + 1);
            str[i] = '_';
            str[i + 1] = tolower((unsigned char)str[i + 1]);
            len++;
            i++;
        }
    }
    return new_str;
}

int main() {
    char str[256];
    printf("Enter a camel case string: ");
    scanf("%255s", str);
    camel_to_snake(str);
    printf("Snake case: %s\n", str);
    return 0;
}