#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 12, got <no output>
  *  test case 1 failed: expected 6, got <no output>
  */

int count_substrings(const char *str, size_t len) {
    if (len == 0) {
        return 0;
    }
    
    int *prefix = (int *)malloc((len + 1) * sizeof(int));
    if (prefix == NULL) {
        return -1;
    }
    
    prefix[0] = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            free(prefix);
            return -1;
        }
        prefix[i + 1] = prefix[i] + (str[i] - '0');
    }
    
    int count = 0;
    for (size_t sublen = 1; sublen <= len; sublen++) {
        for (size_t i = 0; i <= len - sublen; i++) {
            size_t substring_len = sublen;
            int sum = prefix[i + substring_len] - prefix[i];
            if (sum >= 0 && (size_t)sum == substring_len) {
                count++;
            }
        }
    }
    
    free(prefix);
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    printf("Enter a numeric string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(input, sizeof(input));
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }
    
    if (len == 0) {
        printf("0\n");
        return 0;
    }
    
    if (len >= sizeof(input)) {
        printf("Invalid input\n");
        return 1;
    }
    
    for (size_t i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            printf("Invalid input\n");
            return 1;
        }
    }
    
    int result = count_substrings(input, len);
    if (result < 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%d\n", result);
    return 0;
}