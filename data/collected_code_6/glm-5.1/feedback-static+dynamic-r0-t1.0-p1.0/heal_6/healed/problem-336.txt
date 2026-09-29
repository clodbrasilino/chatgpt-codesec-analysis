#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    size_t len = strnlen(month, 9);
    if (len != 8) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (tolower((unsigned char)month[i]) != "february"[i]) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    int result = check_28_days(argv[1]);
    printf("%d\n", result);

    return 0;
}