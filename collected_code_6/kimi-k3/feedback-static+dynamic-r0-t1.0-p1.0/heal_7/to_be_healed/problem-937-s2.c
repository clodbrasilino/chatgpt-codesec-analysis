#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 1024

char find_most_common_char(const char *str, int *count) {
    int char_count[UCHAR_MAX + 1] = {0};
    size_t i;
    int max_count = 0;
    char most_common = '\0';
    
    if (str == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return '\0';
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        char_count[c]++;
    }
    
    for (i = 0; i <= UCHAR_MAX; i++) {
        if (char_count[i] > max_count) {
            max_count = char_count[i];
            most_common = (char)i;
        }
    }
    
    *count = max_count;
    return most_common;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    int count = 0;
    char result;
    size_t len;
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    if (strchr(buffer, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    len = strcspn(buffer, "\n");
    buffer[len] = '\0';
    
    if (len == 0) {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }
    
    result = find_most_common_char(buffer, &count);
    
    if (count > 0) {
        printf("Most common character: '%c' (appears %d times)\n", result, count);
    } else {
        printf("No characters found\n");
    }
    
    return EXIT_SUCCESS;
}