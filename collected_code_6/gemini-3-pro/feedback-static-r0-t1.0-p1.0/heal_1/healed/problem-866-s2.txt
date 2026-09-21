#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool equals_ignore_case(const char *a, const char *b);
bool has_31_days(const char *month);

bool equals_ignore_case(const char *a, const char *b) {
    if (a == NULL || b == NULL) {
        return false;
    }
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return false;
        }
        a++;
        b++;
    }
    return *a == *b;
}

bool has_31_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (equals_ignore_case(month, "january") ||
        equals_ignore_case(month, "march") ||
        equals_ignore_case(month, "may") ||
        equals_ignore_case(month, "july") ||
        equals_ignore_case(month, "august") ||
        equals_ignore_case(month, "october") ||
        equals_ignore_case(month, "december")) {
        return true;
    }
    
    return false;
}

int main(void) {
    char input[256];
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        
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