#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

size_t count_uppercase(const char *str)
{
    size_t count = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    const char *test = "Hello World From C Programming";
    size_t result;

    result = count_uppercase(test);

    if (printf("Uppercase count: %zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}