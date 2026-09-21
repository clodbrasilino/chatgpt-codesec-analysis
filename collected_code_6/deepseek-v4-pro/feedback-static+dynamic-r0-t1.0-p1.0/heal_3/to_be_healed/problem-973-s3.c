#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t str_size, int n) {
    if (str == NULL || str_size == 0 || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, str_size);
    if (len == 0) {
        return;
    }
    
    n = n % (int)len;
    if (n == 0) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Assuming condition '(unsigned long)n>len' is false
     */
    if ((size_t)n > len) {
        return;
    }
    
    char *temp = malloc((size_t)n);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }
    
    if (n > 0) {
        /* Possible weaknesses found:
         *  Condition '(unsigned long)n<=len' is always true [knownConditionTrueFalse]
         *  Condition '(unsigned long)n<=len' is always true
         */
        if ((size_t)n <= len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp, str, (size_t)n);
        }
    }
    
    /* Possible weaknesses found:
     *  Condition 'len>=(unsigned long)n' is always true
     *  Condition 'len>=(unsigned long)n' is always true [knownConditionTrueFalse]
     */
    if (len >= (size_t)n) {
        memmove(str, str + n, len - (size_t)n + 1);
    }
    
    /* Possible weaknesses found:
     *  Condition '(unsigned long)n<=len' is always true [knownConditionTrueFalse]
     *  Condition '(unsigned long)n<=len' is always true
     */
    if ((size_t)n <= len) {
        /* Possible weaknesses found:
         *  Invalid test for overflow 'str+len-(unsigned long)n<str+len'; pointer overflow is undefined behavior. Some mainstream compilers remove such overflow tests when optimising the code and assume it's always true. [invalidTestForOverflow]
         */
        if (str + len - (size_t)n >= str && str + len - (size_t)n < str + len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(str + len - (size_t)n, temp, (size_t)n);
        }
    }
    
    free(temp);
}

int main(void) {
    char str[] = "HelloWorld";
    int rotations = 3;
    
    printf("Original string: %s\n", str);
    left_rotate_string(str, sizeof(str), rotations);
    printf("After left rotation by %d: %s\n", rotations, str);
    
    return 0;
}