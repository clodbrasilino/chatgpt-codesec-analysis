#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int has30Days(const char *month) {
    if (month == NULL) return 0;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(month);
    
    if (len == 0 || len > 31) return 0;
    
    char *lower = malloc(len + 1);
    if (lower == NULL) return 0;
    
    for (size_t i = 0; i < len; i++) {
        lower[i] = tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';
    
    const char *months30[] = {"april", "june", "september", "november"};
    int result = 0;
    for (int i = 0; i < 4; i++) {
        if (strcmp(lower, months30[i]) == 0) {
            result = 1;
            break;
        }
    }
    
    free(lower);
    return result;
}

int main(void) {
    const char *testMonths[] = {"January", "April", "June", "September", "November", "December", NULL};
    
    for (int i = 0; testMonths[i] != NULL; i++) {
        printf("%s has 30 days: %s\n", testMonths[i], has30Days(testMonths[i]) ? "Yes" : "No");
    }
    
    return 0;
}