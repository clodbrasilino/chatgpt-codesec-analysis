#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_thirty_one_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    const char *thirty_one_days[] = {"january", "march", "may", "july", "august", "october", "december", NULL};
    
    for (size_t i = 0; thirty_one_days[i] != NULL; ++i) {
        size_t j = 0;
        while (thirty_one_days[i][j] != '\0') {
            if (tolower((unsigned char)month[j]) != thirty_one_days[i][j]) {
                break;
            }
            j++;
        }
        if (thirty_one_days[i][j] == '\0' && month[j] == '\0') {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December",
        "InvalidMonth", NULL
    };

    size_t count = sizeof(months) / sizeof(months[0]);

    for (size_t i = 0; i < count; ++i) {
        int result = has_thirty_one_days(months[i]);
        if (result) {
            printf("%s has 31 days.\n", months[i] ? months[i] : "NULL");
        } else {
            printf("%s does not have 31 days.\n", months[i] ? months[i] : "NULL");
        }
    }

    return 0;
}