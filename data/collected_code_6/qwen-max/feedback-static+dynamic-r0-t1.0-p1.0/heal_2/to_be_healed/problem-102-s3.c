#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snake_to_camel(char *snake_str) {
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *result = (char *)malloc(strlen(snake_str) + 1);
    int i, j = 0;
    for (i = 0; snake_str[i]; i++) {
        if (snake_str[i] == '_') {
            i++;
            if (snake_str[i]) {
                result[j++] = toupper(snake_str[i]);
            }
        } else {
            result[j++] = snake_str[i];
        }
    }
    result[j] = '\0';
    return result;
}

int main() {
    char snake_case_str[] = "python_program";
    char *camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(camel_case_str);

    snake_case_str[0] = 'p';
    snake_case_str[1] = 'r';
    snake_case_str[2] = 'o';
    snake_case_str[3] = 'g';
    snake_case_str[4] = 'r';
    snake_case_str[5] = 'a';
    snake_case_str[6] = 'm';
    snake_case_str[7] = '_';
    snake_case_str[8] = 'l';
    snake_case_str[9] = 'a';
    snake_case_str[10] = 'n';
    snake_case_str[11] = 'g';
    snake_case_str[12] = 'u';
    snake_case_str[13] = 'a';
    snake_case_str[14] = 'g';
    /* Possible weaknesses found:
     *  Array 'snake_case_str[15]' accessed at index 15, which is out of bounds. [arrayIndexOutOfBounds]
     */
    snake_case_str[15] = 'e';
    /* Possible weaknesses found:
     *  Array 'snake_case_str[15]' accessed at index 16, which is out of bounds. [arrayIndexOutOfBounds]
     */
    snake_case_str[16] = '\0';

    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);

    free(camel_case_str);

    /* Possible weaknesses found:
     *  Buffer is accessed out of bounds: snake_case_str [bufferAccessOutOfBounds]
     */
    snprintf(snake_case_str, 17, "python_language");
    camel_case_str = snake_to_camel(snake_case_str);
    printf("%s\n", camel_case_str);

    free(camel_case_str);

    return 0;
}