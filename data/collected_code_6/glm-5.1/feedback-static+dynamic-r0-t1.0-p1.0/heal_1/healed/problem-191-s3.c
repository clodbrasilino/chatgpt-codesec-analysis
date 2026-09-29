#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_30_days(const char *month) {
    if (month == NULL) {
        return false;
    }

    if (strcmp(month, "April") == 0) {
        return true;
    }
    if (strcmp(month, "June") == 0) {
        return true;
    }
    if (strcmp(month, "September") == 0) {
        return true;
    }
    if (strcmp(month, "November") == 0) {
        return true;
    }

    return false;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    if (has_30_days(argv[1])) {
        printf("%s has 30 days\n", argv[1]);
    } else {
        printf("%s does not have 30 days\n", argv[1]);
    }

    return 0;
}