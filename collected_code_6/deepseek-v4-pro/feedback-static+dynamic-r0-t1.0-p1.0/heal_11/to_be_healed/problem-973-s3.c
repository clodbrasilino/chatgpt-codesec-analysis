#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void left_rotate_string(char *str, size_t str_size, int n) {
    if (str == NULL || str_size == 0 || n <= 0) {
        return;
    }
    
    size_t len = strnlen(str, str_size);
    if (len == 0 || len >= str_size) {
        return;
    }
    
    n = n % (int)len;
    if (n == 0) {
        return;
    }
    
    size_t temp_size = (size_t)n;
    /* Possible weaknesses found:
     *  Assuming that condition 'temp_size>=len' is not redundant
     *  Assuming condition 'temp_size>=str_size' is false
     */
    if (temp_size >= len || temp_size >= str_size) {
        return;
    }
    
    char *temp = malloc(temp_size + 1);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp == NULL) {
        return;
    }
    
    /* Possible weaknesses found:
     *  Condition 'temp_size<=len' is always true [knownConditionTrueFalse]
     *  Condition 'temp_size<str_size' is always true [knownConditionTrueFalse]
     *  Condition 'temp_size<str_size' is always true
     *  Condition 'temp_size<=len' is always true
     */
    if (temp_size < str_size && temp_size <= len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, str, temp_size);
    } else {
        free(temp);
        return;
    }
    temp[temp_size] = '\0';
    
    size_t remaining = len - temp_size;
    /* Possible weaknesses found:
     *  Assuming condition 'remaining>=str_size' is false
     */
    if (remaining >= str_size) {
        free(temp);
        return;
    }
    
    memmove(str, str + n, remaining);
    str[remaining] = '\0';
    
    size_t copy_start = remaining;
    /* Possible weaknesses found:
     *  Condition 'copy_start>=str_size' is always false [knownConditionTrueFalse]
     *  Condition 'copy_start>=str_size' is always false
     */
    if (copy_start >= str_size) {
        free(temp);
        return;
    }
    
    size_t space_left = str_size - copy_start;
    size_t copy_size = temp_size;
    if (copy_size > space_left) {
        copy_size = space_left;
    }
    
    if (copy_size > 0 && copy_start + copy_size <= str_size) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(str + copy_start, temp, copy_size);
    }
    
    if (copy_start + copy_size < str_size) {
        str[copy_start + copy_size] = '\0';
    } else if (str_size > 0) {
        str[str_size - 1] = '\0';
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