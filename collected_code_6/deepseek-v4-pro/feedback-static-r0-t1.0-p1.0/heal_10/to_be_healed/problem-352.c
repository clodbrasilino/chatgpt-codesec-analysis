#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'calloc'
  */

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return false;
    }

    unsigned char *seen = NULL;
    bool result = true;
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'calloc'
     *  call to undeclared library function 'calloc' with type 'void *(unsigned long, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    seen = (unsigned char *)calloc(UCHAR_MAX + 1, sizeof(unsigned char));
    if (seen == NULL) {
        return false;
    }

    const char *ptr = str;
    size_t count = 0;
    while (*ptr != '\0' && count < (size_t)(UCHAR_MAX + 1)) {
        count++;
        ptr++;
    }
    
    if (*ptr != '\0') {
        /* Possible weaknesses found:
         *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
         *  include '<stdlib.h>' or provide a declaration of 'free'
         *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
         */
        free(seen);
        return false;
    }

    for (size_t i = 0; i < count; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (seen[ch]) {
            result = false;
            break;
        }
        seen[ch] = 1;
    }

    free(seen);
    return result;
}

int main(void) {
    const char *test1 = "abcdef";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "aA";

    printf("Test 1: %s\n", all_unique_chars(test1) ? "true" : "false");
    printf("Test 2: %s\n", all_unique_chars(test2) ? "true" : "false");
    printf("Test 3: %s\n", all_unique_chars(test3) ? "true" : "false");
    printf("Test 4: %s\n", all_unique_chars(test4) ? "true" : "false");

    return 0;
}