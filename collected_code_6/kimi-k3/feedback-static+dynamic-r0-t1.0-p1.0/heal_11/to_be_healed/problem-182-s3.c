#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define MAX_INPUT 1024
#define NUM_PATTERNS 4

int check_patterns(const char *input, int *results, size_t results_size) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *patterns[NUM_PATTERNS] = {
        "[A-Z]",
        "[a-z]",
        "[0-9]",
        "[^A-Za-z0-9]"
    };
    
    regex_t regex;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;
    int status = 0;
    
    if (input == NULL || results == NULL || results_size < NUM_PATTERNS) {
        return -1;
    }
    
    if (strnlen(input, MAX_INPUT + 1) > MAX_INPUT) {
        return -1;
    }
    
    for (i = 0; i < NUM_PATTERNS; i++) {
        results[i] = 0;
    }
    
    for (i = 0; i < NUM_PATTERNS; i++) {
        ret = regcomp(&regex, patterns[i], REG_EXTENDED | REG_NOSUB);
        if (ret != 0) {
            status = -1;
            break;
        }
        
        ret = regexec(&regex, input, 0, NULL, 0);
        if (ret == 0) {
            results[i] = 1;
        } else if (ret != REG_NOMATCH) {
            regfree(&regex);
            status = -1;
            break;
        }
        
        regfree(&regex);
    }
    
    return status;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT + 1];
    int results[NUM_PATTERNS];
    int status;
    size_t len;
    int c;
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    len = strnlen(input, sizeof(input));
    
    if (len == sizeof(input)) {
        fprintf(stderr, "Input not null-terminated\n");
        return EXIT_FAILURE;
    }
    
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    status = check_patterns(input, results, NUM_PATTERNS);
    if (status != 0) {
        fprintf(stderr, "Error processing patterns\n");
        return EXIT_FAILURE;
    }
    
    printf("Uppercase letters: %s\n", results[0] ? "Found" : "Not found");
    printf("Lowercase letters: %s\n", results[1] ? "Found" : "Not found");
    printf("Numeric values: %s\n", results[2] ? "Found" : "Not found");
    printf("Special characters: %s\n", results[3] ? "Found" : "Not found");
    
    return EXIT_SUCCESS;
}