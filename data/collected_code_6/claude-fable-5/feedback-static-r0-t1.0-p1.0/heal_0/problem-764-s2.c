#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

size_t count_numeric(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            count++;
        }
        str++;
    }

    return count;
}

int main(void)
{
    char buffer[256];
    size_t result;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    result = count_numeric(buffer);

    printf("Number of numeric characters: %zu\n", result);

    return 0;
}