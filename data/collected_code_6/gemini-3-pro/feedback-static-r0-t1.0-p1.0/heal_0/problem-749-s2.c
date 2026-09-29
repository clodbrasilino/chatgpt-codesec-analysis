#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_numeric_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    long long num1 = strtoll(str1, NULL, 10);
    long long num2 = strtoll(str2, NULL, 10);

    if (num1 < num2) {
        return -1;
    } else if (num1 > num2) {
        return 1;
    } else {
        return 0;
    }
}

void sort_numeric_strings(char **strings, size_t count) {
    if (strings == NULL || count == 0) {
        return;
    }
    qsort(strings, count, sizeof(char *), compare_numeric_strings);
}

int main(void) {
    char *strings[] = {
        "100",
        "25",
        "5",
        "1000",
        "50",
        "-10",
        "0"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);

    sort_numeric_strings(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}