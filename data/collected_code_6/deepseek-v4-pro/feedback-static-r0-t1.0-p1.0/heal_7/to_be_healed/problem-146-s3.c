#include <stdio.h>
#include <string.h>
#include <stddef.h>

int total_ascii_value(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int total = 0;
    size_t i = 0;
    
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    while (str[i] != '\0' && i < 256) {
        total += (unsigned char)str[i];
        i++;
    }
    
    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        str[0] = '\0';
    } else {
        size_t len = strnlen(str, sizeof(str));
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        } else if (len == sizeof(str) - 1 && str[len - 1] != '\n') {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    int result = total_ascii_value(str);
    printf("Total ASCII value: %d\n", result);
    
    return 0;
}