#include <stdio.h>

static int matches(const char *string)
{
    if (string == NULL || string[0] != 'a') {
        return 0;
    }

    return string[1] == '\0' ||
           (string[1] == 'b' && string[2] == '\0');
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        const char *program = (argc > 0 && argv[0] != NULL) ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program) < 0) {
            return 2;
        }

        return 1;
    }

    if (printf("%s\n", matches(argv[1]) ? "match" : "no match") < 0) {
        return 2;
    }

    return 0;
}