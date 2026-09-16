#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  */

char *camel_to_snake(char *str) {
    if (str == NULL) return NULL;

    static char result[100];
    int i, j = 0;
    for (i = 0; str[i]; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && (!isupper((unsigned char)str[i-1]))) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    strcpy(str, result);
    return str;
}

int main() {
    char str[] = "ThisIsCamelCase";
    camel_to_snake(str);
    printf("Converted string: %s\n", str);

    char str2[] = "PythonLanguage";
    camel_to_snake(str2);
    printf("Converted string: %s\n", str2);

    char str3[] = "PythonProgram";
    camel_to_snake(str3);
    printf("Converted string: %s\n", str3);

    return 0;
}