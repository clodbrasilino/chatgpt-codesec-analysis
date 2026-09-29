#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define MAX_INPUT_SIZE 4096

int count_same_position(const char *str) {
    int count = 0;
    size_t i;
    size_t len;
    
    if (str == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    
    /* Possible weaknesses found:
     *  Condition 'str[i]!='\0'' is always true [knownConditionTrueFalse]
     */
    for (i = 0; i < MAX_INPUT_SIZE && i < len && str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            char lower = tolower((unsigned char)str[i]);
            if ((int)(lower - 'a') == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_SIZE];
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     */
    int c;
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    if (memchr(buffer, '\0', sizeof(buffer)) == NULL) {
        buffer[sizeof(buffer) - 1] = '\0';
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(buffer);
    if (input_len > 0 && buffer[input_len - 1] == '\n') {
        buffer[input_len - 1] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        if (ferror(stdin)) {
            clearerr(stdin);
        }
    }
    
    int result = count_same_position(buffer);
    printf("%d\n", result);
    
    return 0;
}