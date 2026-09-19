#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int count_char(const char *str, char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'PythonLanguage', got Python_Languag
  *  test case 2 failed: expected 'ProgrammingLanguage', got Programming_Languag
  *  test case 0 failed: expected 'PythonProgram', got Python_Progra
  */

char* snake_to_camel(const char *snake_str) {
    int len = strlen(snake_str);
    char *camel_str = (char *)malloc((len + 1) * sizeof(char));
    if (!camel_str) return NULL;

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i == 0 || snake_str[i - 1] == '_') {
            camel_str[j++] = toupper((unsigned char)snake_str[i]);
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    camel_str[len - count_char(snake_str, '_')] = '\0';
    return camel_str;
}

int main() {
    const char test_case_0[] = "python_program";
    const char test_case_1[] = "python_language";
    const char test_case_2[] = "programming_language";

    char *result0 = snake_to_camel(test_case_0);
    printf("%s\n", result0);
    free(result0);

    char *result1 = snake_to_camel(test_case_1);
    printf("%s\n", result1);
    free(result1);

    char *result2 = snake_to_camel(test_case_2);
    printf("%s\n", result2);
    free(result2);

    return 0;
}