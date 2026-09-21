#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

void reverse_substring(char *start, char *end) {
    if (start == NULL || end == NULL || start >= end) {
        return;
    }
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

bool reverse_words(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return false;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0 || len >= max_len) {
        return false;
    }
    
    char *word_start = NULL;
    char *current = str;
    /* Possible weaknesses found:
     *  Variable 'str_end' can be declared as pointer to const [constVariablePointer]
     */
    char *str_end = str + len;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'current<str_end' is not redundant
     */
    while (current < str_end && *current != '\0') {
        if (word_start == NULL && !isspace((unsigned char)*current)) {
            word_start = current;
        }
        if (word_start != NULL && 
            (current + 1 >= str_end || 
             isspace((unsigned char)*(current + 1)) || 
             *(current + 1) == '\0')) {
            /* Possible weaknesses found:
             *  Condition 'current>=str_end' is always false [knownConditionTrueFalse]
             *  Condition 'current>=str_end' is always false
             */
            if (current >= str_end) {
                return false;
            }
            reverse_substring(word_start, current);
            word_start = NULL;
        }
        current++;
    }
    
    if (current > str) {
        reverse_substring(str, current - 1);
    }
    
    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len >= sizeof(buffer)) {
        return EXIT_FAILURE;
    }
    
    size_t newline_pos = strcspn(buffer, "\n");
    if (newline_pos < sizeof(buffer)) {
        buffer[newline_pos] = '\0';
    }
    
    if (!reverse_words(buffer, sizeof(buffer))) {
        return EXIT_FAILURE;
    }
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}