#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

bool match_ab(const char *str, size_t len) {
    if (len > 0 && str[0] == 'a') {
        if (len == 1 || (len == 2 && str[1] == 'b')) {
            return true;
        }
    }
    return false;
}

int main() {
    const char* test_strings[] = {"a", "ab", "ac", "abc", "b", ""};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strlen'
         */
        size_t length = strlen(test_strings[i]);
        printf("Testing '%s': %s\n", test_strings[i], match_ab(test_strings[i], length) ? "Match" : "No Match");
    }
    return 0;
}