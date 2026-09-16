#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 0 failed: expected 'python_program', got <no output>
  */

char *camel_to_snake(char *str) {
    char *write_ptr = str;
    for (int i = 0, len = strlen(str); i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (write_ptr != str && write_ptr[-1] != '_') {
                *write_ptr++ = '_';
            }
            *write_ptr++ = tolower((unsigned char)str[i]);
        } else {
            *write_ptr++ = str[i];
        }
    }
    *write_ptr = '\0';
    return str;
}

int main() {
    char str[256];
    printf("Enter a camel case string: ");
    fgets(str, 256, stdin);
    str[strcspn(str, "\n")] = 0;
    camel_to_snake(str);
    printf("Snake case: %s\n", str);
    return 0;
}