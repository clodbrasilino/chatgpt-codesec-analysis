#include <stdio.h>
#include <string.h>

int total_ascii_value(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int total = 0;
    size_t i = 0;
    
    while (i < 1024 && str[i] != '\0') {
        total += (unsigned char)str[i];
        i++;
    }
    
    return total;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024] = {0};
    
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    str[strcspn(str, "\n")] = '\0';
    
    int result = total_ascii_value(str);
    printf("Total ASCII value: %d\n", result);
    
    return 0;
}