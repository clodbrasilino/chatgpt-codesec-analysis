#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'free'
  */

bool is_alternating(const char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);

    if (len < 2) {
        return false;
    }

    char a = str[0];
    char b = str[1];

    if (a == b) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != a) {
                return false;
            }
        } else {
            if (str[i] != b) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    char *str = NULL;
    size_t len = 0;
    ssize_t read = getline(&str, &len, stdin);
    
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    if (read != -1) {
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
        if (is_alternating(str, len)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
        /* Possible weaknesses found:
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(str);
    }
    return 0;
}