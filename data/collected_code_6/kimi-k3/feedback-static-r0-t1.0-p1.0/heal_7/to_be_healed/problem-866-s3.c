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
        size_t expectedLen = strnlen(months[j], MAX_MONTH_LEN);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MAX_MONTH_LEN];

    printf("Enter month name: ");
    if (fgets(month, sizeof(month), stdin) != NULL) {
        size_t len = strnlen(month, sizeof(month));
        
        if (len > 0 && month[len - 1] == '\n') {
            month[len - 1] = '\0';
        } else if (len == sizeof(month) - 1 && month[len - 1] != '\n') {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF) {
                if (c == EOF) {
                    break;
                }
            }
        }

        if (has31Days(month)) {
            printf("%s has 31 days.\n", month);
        } else {
            printf("%s does not have 31 days.\n", month);
        }
    }

    return 0;
}