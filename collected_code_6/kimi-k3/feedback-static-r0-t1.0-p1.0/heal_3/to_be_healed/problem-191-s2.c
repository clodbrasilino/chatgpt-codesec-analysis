#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_MONTH_LEN 16

static void trim_whitespace(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    char *start = str;
    char *end;
    
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    if (*start == '\0') {
        *str = '\0';
        return;
    }
    
    size_t len = strnlen(start, size - (size_t)(start - str));
    if (len == 0) {
        *str = '\0';
        return;
    }
    
    end = start + len - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    len = (size_t)(end - start) + 1;
    if (len >= size) {
        len = size - 1;
    }
    
    memmove(str, start, len);
    str[len] = '\0';
}

static bool is_valid_input(const char *month, size_t max_len) {
    if (month == NULL || max_len == 0) {
        return false;
    }
    
    size_t len = strnlen(month, max_len);
    if (len == 0 || len >= max_len) {
        return false;
    }
    
    return true;
}

static bool has_30_days(const char *month) {
    static const char *months_30[] = {
        "april", "june", "september", "november"
    };
    static const size_t num_months = sizeof(months_30) / sizeof(months_30[0]);
    
    if (!is_valid_input(month, MAX_MONTH_LEN)) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char normalized[MAX_MONTH_LEN];
    size_t len = strnlen(month, sizeof(normalized));
    
    if (len >= sizeof(normalized)) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[len] = '\0';
    
    trim_whitespace(normalized, sizeof(normalized));
    
    for (size_t j = 0; j < num_months; j++) {
        if (strcmp(normalized, months_30[j]) == 0) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_MONTH_LEN];
    
    printf("Enter month name: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }
    
    if (has_30_days(input)) {
        printf("The month '%s' has 30 days.\n", input);
    } else {
        printf("The month '%s' does not have 30 days.\n", input);
    }
    
    return EXIT_SUCCESS;
}