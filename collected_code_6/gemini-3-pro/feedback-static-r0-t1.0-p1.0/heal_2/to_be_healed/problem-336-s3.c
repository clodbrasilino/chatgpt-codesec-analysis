#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    if (len >= 32) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[32];
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, month, len + 1);

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
    char month[32];

    if (fgets(month, sizeof(month), stdin) != NULL) {
        month[strcspn(month, "\r\n")] = '\0';
        
        if (has_28_days(month)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}