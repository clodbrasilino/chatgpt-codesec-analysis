#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void to_lowercase(char *str);
bool has_31_days(const char *month);

void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

bool has_31_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char lower_month[32];
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(lower_month, month, sizeof(lower_month) - 1);
    lower_month[sizeof(lower_month) - 1] = '\0';
    
    to_lowercase(lower_month);

    if (strcmp(lower_month, "january") == 0 ||
        strcmp(lower_month, "march") == 0 ||
        strcmp(lower_month, "may") == 0 ||
        strcmp(lower_month, "july") == 0 ||
        strcmp(lower_month, "august") == 0 ||
        strcmp(lower_month, "october") == 0 ||
        strcmp(lower_month, "december") == 0) {
        return true;
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
        
        if (has_31_days(input)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    } else {
        return 1;
    }
    
    return 0;
}