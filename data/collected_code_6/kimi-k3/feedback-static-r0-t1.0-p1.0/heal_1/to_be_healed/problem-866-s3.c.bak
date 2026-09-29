#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has31Days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    const char *months[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    const size_t monthCount = sizeof(months) / sizeof(months[0]);

    char buffer[32];
    size_t i = 0;
    /* Possible weaknesses found:
     *  Array index 'i' is used before limits check. [arrayIndexThenCheck]
     */
    while (month[i] != '\0' && i < sizeof(buffer) - 1) {
        buffer[i] = (char)tolower((unsigned char)month[i]);
        i++;
    }
    buffer[i] = '\0';

    for (size_t j = 0; j < monthCount; j++) {
        if (strcmp(buffer, months[j]) == 0) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    char month[32];

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t len = strlen(month);
        if (len > 0 && month[len - 1] == '\n') {
            month[len - 1] = '\0';
        }

        if (has31Days(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }

    return 0;
}