#include <stdio.h>
#include <limits.h>
#include <stddef.h>

size_t count_most_common_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    const unsigned char *p;
    size_t max = 0;
    int best = 0;

    if (str == NULL || *str == '\0') {
        if (result != NULL) {
            *result = '\0';
        }
        return 0;
    }

    p = (const unsigned char *)str;
    while (*p != '\0') {
        counts[*p]++;
        if (counts[*p] > max) {
            max = counts[*p];
            best = *p;
        }
        p++;
    }

    if (result != NULL) {
        *result = (char)best;
    }
    return max;
}

int main(void)
{
    const char *text = "hello world";
    char c;
    size_t count = count_most_common_char(text, &c);

    printf("Most common character: %c (%zu)\n", c, count);
    return 0;
}