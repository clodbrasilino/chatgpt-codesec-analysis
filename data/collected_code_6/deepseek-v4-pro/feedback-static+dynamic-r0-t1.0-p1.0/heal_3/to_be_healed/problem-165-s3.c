#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

#define MAX_INPUT_SIZE 4096

int count_same_position(const char *str) {
    int count = 0;
    size_t i;
    
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     */
    for (i = 0; str[i] != '\0' && i < INT_MAX; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if ((int)(lower - 'a') >= 0 && (lower - 'a') == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];
    size_t input_len;
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(buffer);
    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == sizeof(buffer) - 1 && buffer[input_len - 1] != '\n') {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
    }
    
    int result = count_same_position(buffer);
    printf("Count: %d\n", result);
    
    return 0;
}