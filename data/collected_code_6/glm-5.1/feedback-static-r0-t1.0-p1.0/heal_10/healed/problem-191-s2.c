#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool has_30_days(const char *month, size_t len) {
    if (month == NULL) {
        return false;
    }

    const char *months[] = {"April", "June", "September", "November"};
    for (size_t i = 0; i < sizeof(months) / sizeof(months[0]); i++) {
        if (strlen(months[i]) == len && strncmp(month, months[i], len) == 0) {
            return true;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    const char *safe_month = argv[1];
    size_t src_len = strnlen(safe_month, 128);
    if (src_len >= 128) {
        fprintf(stderr, "Month name too long\n");
        return 1;
    }

    if (has_30_days(safe_month, src_len)) {
        printf("%s contains 30 days.\n", safe_month);
    } else {
        printf("%s does not contain 30 days.\n", safe_month);
    }

    return 0;
}