#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_30_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (strcmp(month, "April") == 0 || strcmp(month, "June") == 0 || 
        strcmp(month, "September") == 0 || strcmp(month, "November") == 0) {
        return true;
    }

    return false;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    size_t len = strlen(argv[1]);
    if (len >= 128) {
        fprintf(stderr, "Month name too long\n");
        return 1;
    }

    char safe_month[128];
    strncpy(safe_month, argv[1], sizeof(safe_month) - 1);
    safe_month[sizeof(safe_month) - 1] = '\0';

    if (has_30_days(safe_month)) {
        printf("%s contains 30 days.\n", safe_month);
    } else {
        printf("%s does not contain 30 days.\n", safe_month);
    }

    return 0;
}