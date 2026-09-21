#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

bool are_all_chars_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return true;
    }

    char first = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
         *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
         */
        size_t len = strcspn(input, "\n");
        input[len] = '\0';

        if (are_all_chars_same(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}