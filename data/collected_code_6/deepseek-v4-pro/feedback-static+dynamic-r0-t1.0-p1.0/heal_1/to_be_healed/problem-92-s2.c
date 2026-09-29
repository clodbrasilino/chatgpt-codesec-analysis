#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool is_undulating(const char *num) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(num);
    
    if (len < 3) return false;
    
    for (int i = 0; i < len; i++) {
        if (!isdigit((unsigned char)num[i])) return false;
    }
    
    if (num[0] == num[1]) return false;
    
    for (int i = 1; i < len - 1; i++) {
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
    char input[256];
    
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (input[0] == '\0') {
        printf("Empty input\n");
        return 1;
    }
    
    if (is_undulating(input)) {
        printf("%s is an undulating number\n", input);
    } else {
        printf("%s is not an undulating number\n", input);
    }
    
    return 0;
}