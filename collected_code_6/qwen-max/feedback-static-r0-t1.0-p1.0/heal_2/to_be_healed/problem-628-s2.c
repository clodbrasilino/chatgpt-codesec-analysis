#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void replace_spaces(char *str) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i, count = 0, len = strlen(str);
    for (i = 0; i < len; i++) {
        if (str[i] == ' ') count++;
    }

    int new_length = len + (count * 2);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *new_str = (char *)malloc(new_length + 1);
    if (new_str == NULL) return;

    for (i = len - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            new_str[new_length - 1] = '0';
            new_str[new_length - 2] = '2';
            new_str[new_length - 3] = '%';
            new_length -= 3;
        } else {
            new_str[new_length - 1] = str[i];
            new_length--;
        }
    }
    new_str[new_length] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, new_str);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(new_str);
}

int main() {
    char str1[] = "Mr John Smith    ";
    replace_spaces(str1);
    printf("Replaced string: %s\n", str1);

    char str2[] = " Test String with Spaces  ";
    replace_spaces(str2);
    printf("Replaced string: %s\n", str2);

    return 0;
}