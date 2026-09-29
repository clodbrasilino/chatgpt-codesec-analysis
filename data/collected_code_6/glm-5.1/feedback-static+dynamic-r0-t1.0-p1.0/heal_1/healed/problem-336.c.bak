#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_28_days(const char *month) {
    if (month == NULL) {
        return 0;
    }

    char lower[10];
    size_t len = strlen(month);
    if (len == 0 || len >= sizeof(lower)) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        lower[i] = (char)tolower((unsigned char)month[i]);
    }
    lower[len] = '\0';

    if (strcmp(lower, "february") == 0) {
        return 1;
    }

    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <month_name>\n", argv[0]);
        return 1;
    }

    int result = check_28_days(argv[1]);
    printf("%d\n", result);

    return 0;
}