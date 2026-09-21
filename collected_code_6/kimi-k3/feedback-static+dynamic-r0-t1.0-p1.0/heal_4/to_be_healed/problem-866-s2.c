#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has31Days(const char *month) {
    if (month == NULL) {
        return 0;
    }
    
    const char *months31[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lowerMonth[20];
    size_t i;
    size_t len = strnlen(month, sizeof(lowerMonth) - 1);
    
    if (len == 0 || len >= sizeof(lowerMonth) - 1) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        lowerMonth[i] = (char)tolower((unsigned char)month[i]);
    }
    lowerMonth[len] = '\0';
    
    for (i = 0; i < sizeof(months31) / sizeof(months31[0]); i++) {
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
    char month[20];
    
    printf("Enter month name: ");
    
    if (fgets(month, sizeof(month), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(month, sizeof(month));
    if (len > 0 && month[len - 1] == '\n') {
        month[len - 1] = '\0';
    }
    
    if (has31Days(month)) {
        printf("%s has 31 days.\n", month);
    } else {
        printf("%s does not have 31 days.\n", month);
    }
    
    return 0;
}