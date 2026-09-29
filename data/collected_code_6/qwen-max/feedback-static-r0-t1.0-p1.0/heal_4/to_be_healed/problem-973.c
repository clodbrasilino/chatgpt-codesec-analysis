#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

void left_rotate(char *str, size_t len, int d) {
    d = (d % (int)len + len) % len;
    if (d == 0) return;

    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     */
    char *temp = malloc(d + 1);
    if (temp == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, str, d);
    memmove(str, str + d, len - d + 1);
    temp[d] = '\0';
    /* Possible weaknesses found:
     * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
     */
    strcat(str + len - d, temp);

    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(temp);
}

int main() {
    char str[] = "abcdef";
    int d = 2;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    left_rotate(str, strlen(str), d);
    printf("%s\n", str);
    return 0;
}