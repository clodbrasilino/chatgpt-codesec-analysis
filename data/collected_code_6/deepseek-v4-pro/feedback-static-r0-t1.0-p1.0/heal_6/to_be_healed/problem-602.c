#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256
#define INPUT_BUFFER_SIZE 256

char find_first_repeated_char(const char *str) {
    int count[MAX_CHAR] = {0};
    
    if (str == NULL) {
        return '\0';
    }
    
    for (size_t i = 0; i < INPUT_BUFFER_SIZE && str[i] != '\0'; i++) {
        if (count[(unsigned char)str[i]] == 1) {
            return str[i];
        }
        count[(unsigned char)str[i]]++;
    }
    
    return '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_BUFFER_SIZE] = {0};
    
    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    size_t len = 0;
    while (len < INPUT_BUFFER_SIZE && input[len] != '\0') {
        len++;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'len==0' is not redundant
     */
    if (len == 0) {
        printf("No repeated character found\n");
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Condition 'len>0' is always true [knownConditionTrueFalse]
     *  Condition 'len>0' is always true
     */
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (c == EOF) {
            clearerr(stdin);
        }
    }
    
    char result = find_first_repeated_char(input);
    
    if (result != '\0') {
        printf("First repeated character: %c\n", result);
    } else {
        printf("No repeated character found\n");
    }
    
    return 0;
}