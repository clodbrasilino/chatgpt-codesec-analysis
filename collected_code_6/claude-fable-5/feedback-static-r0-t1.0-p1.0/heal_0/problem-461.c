#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t count_uppercase(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isupper((unsigned char)*str)) {
            count++;
        }
        str++;
    }

    return count;
}

int main(void)
{
    const char *text = "Hello World, This Is A Test String!";
    size_t result;

    result = count_uppercase(text);

    if (printf("Uppercase count: %zu\n", result) < 0) {
        return 1;
    }

    return 0;
}