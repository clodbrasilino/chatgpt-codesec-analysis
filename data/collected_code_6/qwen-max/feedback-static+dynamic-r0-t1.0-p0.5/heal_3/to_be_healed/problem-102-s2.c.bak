#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* snake_to_camel(char *snake_str) {
    int len = strlen(snake_str);
    char *camel_str = snake_str;
    /* Possible weaknesses found:
     *  Variable 'capitalize_next' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'capitalize_next' can be reduced. [variableScope]
     */
    int capitalize_next = 0;

    for (int i = 0, j = 0; i <= len; i++) {
        if (i == 0 || snake_str[i] == '_') {
            camel_str[j++] = toupper((unsigned char)snake_str[i + 1]);
            i++;
            /* Possible weaknesses found:
             *  Variable 'capitalize_next' is assigned a value that is never used. [unreadVariable]
             */
            capitalize_next = 0;
        } else {
            camel_str[j++] = snake_str[i];
        }
    }
    /* Possible weaknesses found:
     *  previous implicit declaration is here
     *  call to undeclared function 'count_char'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'count_char'; did you mean 'putchar'? [-Wimplicit-function-declaration]
     *  previous implicit declaration of 'count_char' with type 'int()'
     */
    camel_str[len - count_char(snake_str, '_')] = '\0';
    return camel_str;
}

/* Possible weaknesses found:
 *  an argument type that has a default promotion cannot match an empty parameter name list declaration
 *  conflicting types for 'count_char'
 *  Parameter 'str' can be declared as pointer to const [constParameterPointer]
 *  conflicting types for 'count_char'; have 'int(char *, char)'
 */
int count_char(char *str, char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char test_case_0[] = "python_program";
    char test_case_1[] = "python_language";
    char test_case_2[] = "programming_language";

    printf("%s\n", snake_to_camel(test_case_0));
    printf("%s\n", snake_to_camel(test_case_1));
    printf("%s\n", snake_to_camel(test_case_2));

    return 0;
}