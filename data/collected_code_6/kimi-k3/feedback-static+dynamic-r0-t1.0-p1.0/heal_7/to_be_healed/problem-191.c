#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_MONTH_LEN 16

static bool has_30_days(const char *month)
{
    static const char *const months_30[] = {
        "April", "June", "September", "November"
    };
    size_t i;

    if (month == NULL) {
        return false;
    }

    for (i = 0; i < sizeof(months_30) / sizeof(months_30[0]); i++) {
        if (strcmp(month, months_30[i]) == 0) {
            return true;
        }
    }

    return false;
}

static void trim_newline(char *str, size_t size)
{
    size_t len;

    if (str == NULL || size == 0) {
        return;
    }

    len = strnlen(str, size);
    if (len == size) {
        str[size - 1] = '\0';
        return;
    }

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char month[MAX_MONTH_LEN];

    if (printf("Enter month name: ") < 0) {
        return 1;
    }

    if (fgets(month, sizeof(month), stdin) == NULL) {
        return 1;
    }

    month[sizeof(month) - 1] = '\0';
    trim_newline(month, sizeof(month));

    if (has_30_days(month)) {
        if (printf("%s has 30 days.\n", month) < 0) {
            return 1;
        }
    } else {
        if (printf("%s does not have 30 days.\n", month) < 0) {
            return 1;
        }
    }

    return 0;
}