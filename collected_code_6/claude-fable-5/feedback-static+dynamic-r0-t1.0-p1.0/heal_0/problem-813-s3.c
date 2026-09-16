#include <stdio.h>
#include <stddef.h>

size_t string_length(const char *str)
{
    size_t length = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int main(void)
{
    const char *test_string = "Hello, World!";
    size_t length;

    length = string_length(test_string);

    if (printf("Length of \"%s\" is %zu\n", test_string, length) < 0) {
        return 1;
    }

    length = string_length(NULL);

    if (printf("Length of NULL string is %zu\n", length) < 0) {
        return 1;
    }

    return 0;
}