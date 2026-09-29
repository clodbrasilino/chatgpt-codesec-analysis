#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    size_t len = 0;
    while (len < 32 && month[len] != '\0') {
        len++;
    }

    if (len >= 32) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32] = {0};
    for (size_t i = 0; i < len; i++) {
        buffer[i] = month[i];
    }
    buffer[len] = '\0';

    to_lowercase(buffer);

    if (strcmp(buffer, "february") == 0) {
        return true;
    }
    
    const char *other_months[] = {
        "january", "march", "april", "may", "june",
        "july", "august", "september", "october",
        "november", "december"
    };
    
    for (int i = 0; i < 11; i++) {
        if (strcmp(buffer, other_months[i]) == 0) {
            return false;
        }
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32] = {0};

    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t newline_idx = strcspn(month, "\r\n");
        if (newline_idx < sizeof(month)) {
            month[newline_idx] = '\0';
        }
        
        if (has_28_days(month)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}