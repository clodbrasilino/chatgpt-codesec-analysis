#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

static bool equals_ignore_case(const char *a, const char *b) {
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

bool has_28_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (equals_ignore_case(month, "february")) {
        return true;
    }

    return false;
}

int main(void) {
    size_t buffer_size = 256;
    char *month = (char *)malloc(buffer_size);
    
    if (month == NULL) {
        return 1;
    }

    if (fgets(month, buffer_size, stdin) != NULL) {
        month[strcspn(month, " \t\r\n")] = '\0';
        
        if (month[0] != '\0') {
            if (has_28_days(month)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
        }
    }

    free(month);
    return 0;
}