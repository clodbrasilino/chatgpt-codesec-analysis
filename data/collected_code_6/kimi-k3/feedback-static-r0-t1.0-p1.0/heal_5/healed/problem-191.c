#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

static bool is_valid_month_name(const char *month, size_t size)
{
    size_t len;
    size_t i;

    if (month == NULL || size == 0) {
        return false;
    }

    len = strnlen(month, size);
    if (len == 0 || len >= size || len >= MAX_MONTH_LEN - 1) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (!((month[i] >= 'A' && month[i] <= 'Z') || 
              (month[i] >= 'a' && month[i] <= 'z'))) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    char *month = NULL;
    size_t month_size = MAX_MONTH_LEN;
    ssize_t read_len;

    month = (char *)malloc(month_size);
    if (month == NULL) {
        return 1;
    }

    if (printf("Enter month name: ") < 0) {
        free(month);
        return 1;
    }

    if (fflush(stdout) != 0) {
        free(month);
        return 1;
    }

    read_len = getline(&month, &month_size, stdin);
    if (read_len < 0) {
        free(month);
        return 1;
    }

    trim_newline(month, month_size);

    if (!is_valid_month_name(month, month_size)) {
        if (fprintf(stderr, "Invalid month name.\n") < 0) {
            free(month);
            return 1;
        }
        free(month);
        return 1;
    }

    if (has_30_days(month)) {
        if (printf("%s has 30 days.\n", month) < 0) {
            free(month);
            return 1;
        }
    } else {
        if (printf("%s does not have 30 days.\n", month) < 0) {
            free(month);
            return 1;
        }
    }

    free(month);
    return 0;
}