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

    size_t len = strlen(month);
    if (len >= 32) {
        return false;
    }

    char buffer[32];
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