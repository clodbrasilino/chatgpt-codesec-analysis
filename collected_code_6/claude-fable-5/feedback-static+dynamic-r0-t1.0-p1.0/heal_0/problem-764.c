#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t count_numeric(const char *str)
{
    size_t count = 0;
    size_t i = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            count++;
        }
        i++;
    }

    return count;
}

int main(void)
{
    const char *test1 = "abc123def45";
    const char *test2 = "no digits here";
    const char *test3 = "9876543210";
    size_t result;

    result = count_numeric(test1);
    if (printf("Digits in \"%s\": %zu\n", test1, result) < 0) {
        return 1;
    }

    result = count_numeric(test2);
    if (printf("Digits in \"%s\": %zu\n", test2, result) < 0) {
        return 1;
    }

    result = count_numeric(test3);
    if (printf("Digits in \"%s\": %zu\n", test3, result) < 0) {
        return 1;
    }

    result = count_numeric(NULL);
    if (printf("Digits in NULL: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}