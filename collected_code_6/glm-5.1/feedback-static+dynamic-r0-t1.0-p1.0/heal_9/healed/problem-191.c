#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    char lower[16];
    size_t max_len = sizeof(lower) - 1;

    for (size_t i = 0; i < max_len; i++) {
        if (month[i] == '\0') {
            lower[i] = '\0';
            
            if (strcmp(lower, "april") == 0 || strcmp(lower, "jun") == 0 ||
                strcmp(lower, "june") == 0 || strcmp(lower, "sep") == 0 ||
                strcmp(lower, "september") == 0 || strcmp(lower, "nov") == 0 ||
                strcmp(lower, "november") == 0) {
                return 1;
            }
            
            return 0;
        }
        lower[i] = (char)tolower((unsigned char)month[i]);
    }

    lower[max_len] = '\0';
    return 0;
}

int main(void) {
    printf("%d\n", has_30_days("April"));
    printf("%d\n", has_30_days("JUN"));
    printf("%d\n", has_30_days("January"));
    printf("%d\n", has_30_days(NULL));
    printf("%d\n", has_30_days(""));
    return 0;
}