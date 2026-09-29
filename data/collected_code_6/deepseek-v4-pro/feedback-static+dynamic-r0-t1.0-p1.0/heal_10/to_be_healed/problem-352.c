#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'calloc'
  */

bool all_unique_chars(const char *str) {
    if (str == NULL) {
        return false;
    }

    size_t max_length = (size_t)UCHAR_MAX + 1;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'calloc'
     *  implicit declaration of function 'calloc' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'calloc' with type 'void *(unsigned long, unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    unsigned char *seen = (unsigned char *)calloc(max_length, sizeof(unsigned char));
    if (seen == NULL) {
        return false;
    }

    size_t length = 0;
    while (str[length] != '\0') {
        if (length >= UCHAR_MAX) {
            /* Possible weaknesses found:
             *  include '<stdlib.h>' or provide a declaration of 'free'
             *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
             *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
             */
            free(seen);
            return false;
        }
        unsigned char ch = (unsigned char)str[length];
        if (seen[ch]) {
            free(seen);
            return false;
        }
        seen[ch] = 1;
        length++;
    }

    free(seen);
    return true;
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