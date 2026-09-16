#include <stdio.h>
#include <string.h>
#include <ctype.h>

int has_thirty_one_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    char lower[10] = {0};
    size_t len = strlen(month);

    if (len == 0 || len >= sizeof(lower)) {
        return 0;
    }

    for (size_t i = 0; i < len; ++i) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }

    if (strcmp(lower, "january") == 0 || strcmp(lower, "march") == 0 ||
        strcmp(lower, "may") == 0 || strcmp(lower, "july") == 0 ||
        strcmp(lower, "august") == 0 || strcmp(lower, "october") == 0 ||
        strcmp(lower, "december") == 0) {
        return 1;
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