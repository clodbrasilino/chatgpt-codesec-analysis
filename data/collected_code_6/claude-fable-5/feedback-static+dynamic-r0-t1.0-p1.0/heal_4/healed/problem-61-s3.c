#include <stdio.h>
#include <string.h>

int check_string_length(const char *s, size_t max_len)
{
    size_t n;

    if (s == NULL) {
        return -1;
    }

    n = strnlen(s, max_len);
    if (n >= max_len) {
        return -1;
    }

    return (int)n;
}

int main(void)
{
    const char *test_string = "Hello, world!";
    size_t max_len = 64;
    int result;

    result = check_string_length(test_string, max_len);
    if (result < 0) {
        fprintf(stderr, "Error: string is too long or invalid\n");
        return 1;
    }

    printf("String length: %d\n", result);
    return 0;
}