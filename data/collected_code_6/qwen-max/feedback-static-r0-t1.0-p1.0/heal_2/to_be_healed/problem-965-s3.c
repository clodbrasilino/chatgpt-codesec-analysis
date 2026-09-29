#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char *camel_to_snake(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *result = (char *)malloc(len * 2 + 1);
    if (result == NULL) return NULL;

    bool add_underscore = false;
    int j = 0;

    for (int i = 0; i < len; ++i) {
        if (isupper((unsigned char)str[i])) {
            if (i > 0 && !add_underscore) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)str[i]);
            add_underscore = true;
        } else {
            result[j++] = str[i];
            add_underscore = false;
        }
    }
    result[j] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, j + 1);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(result);
    return str;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    printf("Enter a camel case string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0'; // remove newline
        camel_to_snake(str);
        printf("Snake case: %s\n", str);
    }
    return 0;
}