#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_MONTH_LEN 32
#define MAX_INPUT_LEN 64

static void trim_whitespace(char *str) {
    char *start = str;
    char *end;
    
    if (str == NULL) {
        return;
    }
    
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    if (*start == '\0') {
        *str = '\0';
        return;
    }
    
    end = start;
    while (*end != '\0') {
        end++;
    }
    end--;
    
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    size_t len = (size_t)(end - start) + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

static bool is_valid_input(const char *month, size_t max_len) {
    if (month == NULL) {
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
    
    char normalized[MAX_MONTH_LEN];
    size_t len = strnlen(month, MAX_MONTH_LEN);
    size_t copy_len = (len < MAX_MONTH_LEN - 1) ? len : MAX_MONTH_LEN - 1;
    
    for (size_t i = 0; i < copy_len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[copy_len] = '\0';
    
    trim_whitespace(normalized);
    
    for (size_t j = 0; j < num_months; j++) {
        if (strcmp(normalized, months_30[j]) == 0) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    char input[MAX_INPUT_LEN];
    
    printf("Enter month name: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (has_30_days(input)) {
        printf("The month '%s' has 30 days.\n", input);
    } else {
        printf("The month '%s' does not have 30 days.\n", input);
    }
    
    return EXIT_SUCCESS;
}