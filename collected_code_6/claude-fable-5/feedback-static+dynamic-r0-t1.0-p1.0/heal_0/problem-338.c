#include <stdio.h>
#include <string.h>

long count_substrings(const char *str)
{
    long count;
    size_t len;
    size_t i;
    size_t j;

    if (str == NULL) {
        return -1L;
    }

    count = 0L;
    len = strlen(str);

    for (i = 0U; i < len; i++) {
        for (j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    char buffer[256];
    long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strlen(buffer);
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    result = count_substrings(buffer);
    if (result < 0L) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (printf("%ld\n", result) < 0) {
        return 1;
    }

    return 0;
}