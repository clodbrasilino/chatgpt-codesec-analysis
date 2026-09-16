#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_MONTH_LEN 10

static void trim_whitespace(char *str) {
    char *start = str;
    char *end;
    
    while (isspace((unsigned char)*start)) {
        start++;
    }
    
    if (*start == '\0') {
        *str = '\0';
        return;
    }
    
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    size_t len = (size_t)(end - start) + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

static bool is_valid_input(const char *month) {
    if (month == NULL) {
        return false;
    }
    
    size_t len = strlen(month);
    if (len == 0 || len >= MAX_MONTH_LEN) {
        return false;
    }
    
    return true;
}

static bool has_30_days(const char *month) {
    static const char *months_30[] = {
        "april", "june", "september", "november"
    };
    static const size_t num_months = sizeof(months_30) / sizeof(months_30[0]);
    
    if (!is_valid_input(month)) {
        return false;
    }
    
    char normalized[MAX_MONTH_LEN];
    size_t i;
    size_t len = strlen(month);
    
    if (len >= sizeof(normalized)) {
        return false;
    }
    
    for (i = 0; i < len; i++) {
        normalized[i] = (char)tolower((unsigned char)month[i]);
    }
    normalized[i] = '\0';
    
    trim_whitespace(normalized);
    
    for (size_t j = 0; j < num_months; j++) {
        if (strcmp(normalized, months_30[j]) == 0) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    char input[MAX_MONTH_LEN];
    
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