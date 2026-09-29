#include <stdio.h>
#include <string.h>

void remove_first_last_occurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strnlen(str, 256);
    if (len == 0) {
        return;
    }
    
    size_t first = 0;
    size_t last = 0;
    int found_first = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            first = i;
            found_first = 1;
            break;
        }
    }
    
    if (!found_first) {
        return;
    }
    
    for (size_t i = len; i > 0; i--) {
        if (str[i - 1] == ch) {
            last = i - 1;
            break;
        }
    }
    
    if (first == last) {
        memmove(&str[first], &str[first + 1], len - first);
        return;
    }
    
    memmove(&str[first], &str[first + 1], last - first);
    memmove(&str[last - 1], &str[last], len - last + 1);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[256] = "hello world";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[256] = "programming";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str3[256] = "a";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str4[256] = "no match here";
    
    printf("Original: %s\n", str1);
    remove_first_last_occurrence(str1, 'l');
    printf("Modified: %s\n", str1);
    
    printf("Original: %s\n", str2);
    remove_first_last_occurrence(str2, 'r');
    printf("Modified: %s\n", str2);
    
    printf("Original: %s\n", str3);
    remove_first_last_occurrence(str3, 'a');
    printf("Modified: %s\n", str3);
    
    printf("Original: %s\n", str4);
    remove_first_last_occurrence(str4, 'x');
    printf("Modified: %s\n", str4);
    
    return 0;
}