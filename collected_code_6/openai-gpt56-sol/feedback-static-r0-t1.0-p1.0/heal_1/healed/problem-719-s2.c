#include <stdio.h>

static int matches(const char *str)
{
    size_t i;

    if (str == NULL || str[0] != 'a') {
        return 0;
    }

    for (i = 1; str[i] != '\0'; ++i) {
        if (str[i] != 'b') {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char * const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 2;
    }

    if (matches(argv[1])) {
        puts("Match");
        return 0;
    }

    puts("No match");
    return 1;
}