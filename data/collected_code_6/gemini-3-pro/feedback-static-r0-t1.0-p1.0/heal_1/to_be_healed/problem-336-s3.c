#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void to_lowercase(char *str) {
    if (str == NULL) {
        return;
    }
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[20];
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(buffer, month, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

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

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[20];

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%19s", month) == 1) {
        if (has_28_days(month)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}