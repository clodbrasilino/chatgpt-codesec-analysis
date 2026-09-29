#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int case_insensitive_equals(const char *a, const char *b) {
    if (!a || !b) return 0;
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

int has_31_days(const char *month) {
    if (month == NULL) {
        return 0; 
    }

    if (case_insensitive_equals(month, "january") || case_insensitive_equals(month, "jan") ||
        case_insensitive_equals(month, "march")   || case_insensitive_equals(month, "mar") ||
        case_insensitive_equals(month, "may")     ||
        case_insensitive_equals(month, "july")    || case_insensitive_equals(month, "jul") ||
        case_insensitive_equals(month, "august")  || case_insensitive_equals(month, "aug") ||
        case_insensitive_equals(month, "october") || case_insensitive_equals(month, "oct") ||
        case_insensitive_equals(month, "december")|| case_insensitive_equals(month, "dec")) {
        return 1;
    }

    return 0;
}

int main(void) {
    size_t buffer_size = 256;
    char *input = (char *)malloc(buffer_size);
    
    if (input == NULL) {
        return 1;
    }

    if (fgets(input, (int)buffer_size, stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';

        if (has_31_days(input)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    free(input);
    return 0;
}