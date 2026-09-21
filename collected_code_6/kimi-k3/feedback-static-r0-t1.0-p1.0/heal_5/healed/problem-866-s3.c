#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_MONTH_LEN 32

int has31Days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    const char *months[] = {
        "january", "march", "may", "july",
        "august", "october", "december"
    };
    const size_t monthCount = sizeof(months) / sizeof(months[0]);

    size_t monthLen = strnlen(month, MAX_MONTH_LEN);
    
    if (monthLen == 0 || monthLen >= MAX_MONTH_LEN) {
        return 0;
    }

    for (size_t j = 0; j < monthCount; j++) {
        size_t expectedLen = strlen(months[j]);
        if (monthLen != expectedLen) {
            continue;
        }
        
        bool match = true;
        for (size_t i = 0; i < monthLen; i++) {
            if (tolower((unsigned char)month[i]) != months[j][i]) {
                match = false;
                break;
            }
        }
        
        if (match) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    char month[MAX_MONTH_LEN];

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t len = strnlen(month, sizeof(month));
        
        if (len > 0 && month[len - 1] == '\n') {
            month[len - 1] = '\0';
        } else if (len == sizeof(month) - 1 && month[len - 1] != '\n') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }

        if (has31Days(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }

    return 0;
}