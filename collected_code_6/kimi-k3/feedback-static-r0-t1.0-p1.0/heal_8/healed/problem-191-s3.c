#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL || *month == '\0') {
        return 0;
    }
    
    const char *months[] = {"april", "june", "september", "november"};
    const size_t num_months = sizeof(months) / sizeof(months[0]);
    
    size_t len = strnlen(month, 10);
    
    if (len > 9) {
        return 0;
    }
    
    for (size_t i = 0; i < num_months; i++) {
        size_t target_len = strlen(months[i]);
        
        if (len != target_len) {
            continue;
        }
        
        int match = 1;
        for (size_t j = 0; j < len; j++) {
            if (tolower((unsigned char)month[j]) != months[i][j]) {
                match = 0;
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
    char input[64];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    if (has_30_days(input)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}