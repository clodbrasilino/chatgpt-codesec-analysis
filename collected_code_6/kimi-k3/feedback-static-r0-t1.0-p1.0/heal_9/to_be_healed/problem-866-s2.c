#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has31Days(const char *month, size_t month_len) {
    if (month == NULL) {
        return 0;
    }
    
    const char *months31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    
    if (month_len == 0 || month_len > 9) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lowerMonth[10];
    
    for (size_t i = 0; i < month_len && i < sizeof(lowerMonth) - 1; i++) {
        lowerMonth[i] = (char)tolower((unsigned char)month[i]);
    }
    lowerMonth[month_len < sizeof(lowerMonth) ? month_len : sizeof(lowerMonth) - 1] = '\0';
    
    for (size_t i = 0; i < sizeof(months31) / sizeof(months31[0]); i++) {
        if (strcmp(lowerMonth, months31[i]) == 0) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[32];
    
    printf("Enter month name: ");
    
    if (fgets(month, sizeof(month), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strcspn(month, "\n");
    month[len] = '\0';
    
    if (has31Days(month, len)) {
        printf("%s has 31 days.\n", month);
    } else {
        printf("%s does not have 31 days.\n", month);
    }
    
    return 0;
}