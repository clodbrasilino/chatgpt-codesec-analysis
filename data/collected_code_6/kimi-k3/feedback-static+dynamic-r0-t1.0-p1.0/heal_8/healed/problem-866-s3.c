#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has31Days(const char *month, size_t maxLen) {
    if (month == NULL) {
        return 0;
    }

    const char *months[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    const size_t monthCount = sizeof(months) / sizeof(months[0]);

    size_t len = strnlen(month, maxLen);
    if (len > 9) {
        return 0;
    }

    char buffer[10];
    if (len >= sizeof(buffer)) {
        return 0;
    }

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
    char month[64];

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