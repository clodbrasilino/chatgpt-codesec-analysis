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

    char safe_month[128];
    size_t len = strnlen(argv[1], sizeof(safe_month) - 1);
    if (len >= sizeof(safe_month)) {
        fprintf(stderr, "Month name too long\n");
        return 1;
    }

    memcpy(safe_month, argv[1], len);
    safe_month[len] = '\0';

    if (has_30_days(safe_month)) {
        printf("%s contains 30 days.\n", safe_month);
    } else {
        printf("%s does not contain 30 days.\n", safe_month);
    }

    return 0;
}