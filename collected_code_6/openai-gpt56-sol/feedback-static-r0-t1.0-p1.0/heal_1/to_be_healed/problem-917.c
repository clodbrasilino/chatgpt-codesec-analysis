#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    const unsigned char *p = (const unsigned char *)text;
    int found = 0;

    while (*p != '\0') {
        if (isupper(*p) && islower(p[1])) {
            const unsigned char *start = p++;

            while (islower(*p)) {
                ++p;
            }

            if (printf("%.*s\n", (int)(p - start), (const char *)start) < 0) {
                return -1;
            }

            found = 1;
        } else {
            ++p;
        }
    }

    return found;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    int status = EXIT_SUCCESS;

    /* Possible weaknesses found:
     *  Although the value stored to 'length' is used in the enclosing expression, the value is never actually read from 'length' [deadcode.DeadStores]
     */
    while ((length = getline(&line, &capacity, stdin)) != -1) {
        if (find_sequences(line) < 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (ferror(stdin) != 0) {
        status = EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}