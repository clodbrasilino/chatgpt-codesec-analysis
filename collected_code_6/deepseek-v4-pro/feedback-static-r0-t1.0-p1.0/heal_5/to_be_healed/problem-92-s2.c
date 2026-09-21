#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_undulating(const char *num, size_t len) {
    if (len < 3) return false;
    
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)num[i])) return false;
    }
    
    if (num[0] == num[1]) return false;
    
    for (size_t i = 1; i < len - 1; i++) {
        if (num[i] == num[i-1] || num[i] == num[i+1] || num[i-1] != num[i+1]) {
            return false;
        }
    }
    
    return num[len-1] != num[len-2];
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256] = {0};
    size_t input_len;
    bool overflow = false;
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input_len = strnlen(input, sizeof(input));
    if (input_len > 0 && input_len < sizeof(input) && input[input_len - 1] != '\n') {
        if (input_len == sizeof(input) - 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
            overflow = true;
        }
    }
    
    if (overflow) {
        printf("Input too long\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    input_len = strnlen(input, sizeof(input));
    
    if (input_len == 0) {
        printf("Empty input\n");
        return 1;
    }
    
    if (is_undulating(input, input_len)) {
        printf("%s is an undulating number\n", input);
    } else {
        printf("%s is not an undulating number\n", input);
    }
    
    return 0;
}