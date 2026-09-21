#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_MONTH_LEN 9
#define MONTH_BUFFER_SIZE (MAX_MONTH_LEN + 1)

int has31Days(const char *month, size_t maxLen) {
    if (month == NULL || maxLen == 0) {
        return 0;
    }

    const char *months[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    const size_t monthCount = sizeof(months) / sizeof(months[0]);

    size_t len = strnlen(month, maxLen);
    if (len == 0 || len > MAX_MONTH_LEN) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MONTH_BUFFER_SIZE];
    
    for (size_t i = 0; i < len; i++) {
        buffer[i] = (char)tolower((unsigned char)month[i]);
    }
    buffer[len] = '\0';

    for (size_t j = 0; j < monthCount; j++) {
        if (strcmp(buffer, months[j]) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MONTH_BUFFER_SIZE + 1];

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        month[strcspn(month, "\n")] = '\0';

        if (has31Days(month, sizeof(month))) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }

    return 0;
}