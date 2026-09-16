#include <stdio.h>
#include <limits.h>
#include <stddef.h>

size_t count_most_common_char(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t counts[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
        counts[(unsigned char)str[i]]++;
    }

    size_t max_count = 0;
    for (size_t i = 0; i <= UCHAR_MAX; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
        }
    }

    return max_count;
}

int main(void) {
    const char *text = "experienced developer";
    size_t result = count_most_common_char(text);
    printf("%zu\n", result);
    return 0;
}