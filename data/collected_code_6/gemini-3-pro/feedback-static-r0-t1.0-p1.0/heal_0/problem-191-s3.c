#include <stdio.h>
#include <string.h>
#include <strings.h>

int has_30_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    if (strcasecmp(month, "April") == 0 ||
        strcasecmp(month, "June") == 0 ||
        strcasecmp(month, "September") == 0 ||
        strcasecmp(month, "November") == 0) {
        return 1;
    }

    return 0;
}

int main() {
    const char *test_months[] = {
        "April",
        "January",
        "SEPTEMBER",
        "February",
        "June",
        NULL
    };

    for (int i = 0; test_months[i] != NULL; i++) {
        if (has_30_days(test_months[i])) {
            printf("%s has 30 days.\n", test_months[i]);
        } else {
            printf("%s does not have 30 days.\n", test_months[i]);
        }
    }

    return 0;
}