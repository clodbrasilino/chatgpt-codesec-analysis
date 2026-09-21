#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has30Days(const char *month) {
    if (month == NULL) return 0;
    
    size_t len = strnlen(month, 32);
    
    if (len == 0 || len >= 32) return 0;
    
    char lower[32];
    size_t i;
    
    for (i = 0; i < len && i < sizeof(lower) - 1; i++) {
        lower[i] = tolower((unsigned char)month[i]);
    }
    lower[i] = '\0';
    
    const char *months30[] = {"april", "june", "september", "november"};
    for (int j = 0; j < 4; j++) {
        if (strcmp(lower, months30[j]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    const char *testMonths[] = {"January", "April", "June", "September", "November", "December", NULL};
    
    for (int i = 0; testMonths[i] != NULL; i++) {
        printf("%s has 30 days: %s\n", testMonths[i], has30Days(testMonths[i]) ? "Yes" : "No");
    }
    
    return 0;
}