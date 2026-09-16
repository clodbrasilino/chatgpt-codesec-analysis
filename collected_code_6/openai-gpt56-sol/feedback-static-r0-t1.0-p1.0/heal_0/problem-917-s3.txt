#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;

    while (*p != '\0') {
        if (isupper(*p) && islower(p[1])) {
            const unsigned char *start = p++;

            while (islower(*p)) {
                ++p;
            }

            if (printf("%.*s\n", (int)(p - start), (const char *)start) < 0) {
                return -1;
            }
        } else {
            ++p;
        }
    }

    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    int status = EXIT_SUCCESS;

    while (getline(&line, &capacity, stdin) != -1) {
        if (find_sequences(line) != 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (ferror(stdin)) {
        status = EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}