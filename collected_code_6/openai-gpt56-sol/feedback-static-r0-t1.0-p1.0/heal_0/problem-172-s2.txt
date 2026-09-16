#include <stdio.h>
#include <stddef.h>

size_t count_std_occurrences(const char *str)
{
    size_t count = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[0] != '\0' && str[1] != '\0' && str[2] != '\0') {
        if (str[0] == 's' && str[1] == 't' && str[2] == 'd') {
            ++count;
        }
        ++str;
    }

    return count;
}

int main(void)
{
    const char input[] =
        "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    size_t occurrences = count_std_occurrences(input);

    if (printf("%zu\n", occurrences) < 0) {
        return 1;
    }

    return 0;
}