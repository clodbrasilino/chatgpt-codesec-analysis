#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snake_to_camel(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int i, len = strlen(str);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *result = (char *)malloc((len + 1) * sizeof(char));
    if (result == NULL) return NULL;

    for (i = 0, result[0] = '\0'; *str; str++) {
        if (*str == '_') {
            str++;
            if (*str) {
                /* Possible weaknesses found:
                 *  call to undeclared function 'strnfcat'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  implicit declaration of function 'strnfcat'; did you mean 'strncat'? [-Wimplicit-function-declaration]
                 *  did you mean 'strncat'?
                 */
                strnfcat(result, "%c", toupper(*str));
            }
        } else {
            /* Possible weaknesses found:
             *  call to undeclared function 'strnfcat'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            strnfcat(result, "%c", *str);
        }
    }
    return result;
}

int main() {
    char input[] = "this_is_snake_case";
    char *output = snake_to_camel(input);

    if (output != NULL) {
        printf("Camel case: %s\n", output);
        /* Possible weaknesses found:
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         */
        free(output);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}