#include <stdio.h>
#include <limits.h>

int count_most_common_char(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t counts[UCHAR_MAX + 1] = {0};
    const unsigned char *ptr = (const unsigned char *)str;

    while (*ptr != '\0') {
        counts[*ptr]++;
        ptr++;
    }

    size_t max_count = 0;
    for (size_t i = 0; i < (UCHAR_MAX + 1); i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
        }
    }

    return (int)max_count;
}

int main(void) {
    const char *test1 = "hello world";
    const char *test2 = "";
    const char *test3 = NULL;

    printf("%d\n", count_most_common_char(test1));
    printf("%d\n", count_most_common_char(test2));
    printf("%d\n", count_most_common_char(test3));

    return 0;
}