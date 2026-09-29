#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

#define MAX_LEN 102

int matchString(const char* str) {
    int i = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'strnlen' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'strnlen' [-Wbuiltin-declaration-mismatch]
     */
    int len = strnlen(str, MAX_LEN);
    while (i < len - 2) {
        if (str[i] == 'a' && str[i + 2] == 'b') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LEN];
    printf("Enter a string: ");
    fgets(str, MAX_LEN, stdin);
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'strcspn' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
     *  include '<string.h>' or provide a declaration of 'strcspn'
     */
    str[strcspn(str, "\n")] = '\0';
    int result = matchString(str);
    if (result == 1) {
        printf("String matches the pattern.\n");
    } else {
        printf("String does not match the pattern.\n");
    }
    return 0;
}