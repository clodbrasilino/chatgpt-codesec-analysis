#include <stdio.h>
#include <string.h>

int count_std_occurrences(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    int count = 0;
    size_t len = strnlen(str, max_len);
    
    for (size_t i = 0; i + 2 < len; i++) {
        if (str[i] == 's' && str[i + 1] == 't' && str[i + 2] == 'd') {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    int result = count_std_occurrences(buffer, sizeof(buffer));
    
    printf("Occurrences of 'std': %d\n", result);
    
    return 0;
}