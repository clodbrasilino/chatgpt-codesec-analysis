#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_31_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    char lower[10] = {0};
    size_t i;
    for (i = 0; i < 9 && month[i] != '\0'; i++) {
        lower[i] = tolower((unsigned char)month[i]);
    }
    lower[i] = '\0';

    if (strcmp(lower, "january") == 0 ||
        strcmp(lower, "march") == 0 ||
        strcmp(lower, "may") == 0 ||
        strcmp(lower, "july") == 0 ||
        strcmp(lower, "august") == 0 ||
        strcmp(lower, "october") == 0 ||
        strcmp(lower, "december") == 0) {
        return true;
    }

    return false;
}

int main(void) {
    const char *test_months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    for (size_t i = 0; i < sizeof(test_months) / sizeof(test_months[0]); i++) {
        printf("%s: %d\n", test_months[i], has_31_days(test_months[i]));
    }

    return 0;
}