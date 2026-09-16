#include <stdio.h>
#include <string.h>
#include <limits.h>

long long countSubstrings(const char *str)
{
    long long counts[UCHAR_MAX + 1] = {0};
    long long result = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        result += (counts[i] * (counts[i] + 1)) / 2;
    }

    return result;
}

int main(void)
{
    char buffer[1024];
    long long result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = countSubstrings(buffer);

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}