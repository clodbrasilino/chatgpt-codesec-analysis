#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snake_to_camel(const char *snake_str) {
    int len = strlen(snake_str);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *camel_str = (char *)malloc((len + 1) * sizeof(char));
    if (!camel_str) return NULL;

    int j = 0;
    for (int i = 0; i <= len; i++) {
        if (i == 0 || snake_str[i] == '_') {
            camel_str[j++] = toupper((unsigned char)snake_str[i + 1]);
            i++;
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
 *  conflicting types for 'count_char'; have 'int(const char *, char)'
 */
int count_char(const char *str, char c) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    const char test_case_0[] = "python_program";
    const char test_case_1[] = "python_language";
    const char test_case_2[] = "programming_language";

    char *result0 = snake_to_camel(test_case_0);
    printf("%s\n", result0);
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    free(result0);

    char *result1 = snake_to_camel(test_case_1);
    printf("%s\n", result1);
    free(result1);

    char *result2 = snake_to_camel(test_case_2);
    printf("%s\n", result2);
    free(result2);

    return 0;
}