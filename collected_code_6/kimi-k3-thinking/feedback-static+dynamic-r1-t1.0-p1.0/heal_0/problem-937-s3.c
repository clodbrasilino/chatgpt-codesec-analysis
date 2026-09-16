#include <stdio.h>
#include <limits.h>

int find_most_common_char(const char *str, size_t *count);

int find_most_common_char(const char *str, size_t *count)
{
    size_t freq[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    int most_common = -1;

    if (str == NULL || count == NULL) {
        return -1;
    }

    *count = 0;

    while (*str != '\0') {
        freq[(unsigned char)*str]++;
        str++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (freq[i] > max_count) {
            max_count = freq[i];
            most_common = (int)i;
        }
    }

    *count = max_count;

    return most_common;
}

int main(void)
{
    const char *input = "programming in c is fun";
    size_t count = 0;
    int ch = find_most_common_char(input, &count);

    if (ch >= 0) {
        printf("Most common character: '%c'\n", ch);
        printf("Occurrences: %zu\n", count);
    } else {
        printf("The string is empty or invalid.\n");
    }

    return 0;
}