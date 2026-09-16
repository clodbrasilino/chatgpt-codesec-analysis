#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long countSubstrings(const char *str)
{
    long long counts[256] = {0};
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

    for (i = 0; i < 256; i++) {
        result += (counts[i] * (counts[i] + 1)) / 2;
    }

    return result;
}

int main(void)
{
    char buffer[1024];
    size_t len;
    long long result;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = countSubstrings(buffer);

    if (printf("Count of substrings: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}