#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    int count = 0;
    if (str == NULL) {
        return 0;
    }
    size_t n = strnlen(str, 1000);
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = i; j < n; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        int result = countSubstrings(str);
        printf("Number of substrings with same first and last characters: %d\n", result);
    } else {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    return 0;
}