#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

static void capitalize_first_last(char *str)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return;
    }

    len = strnlen(str, BUFFER_SIZE);
    i = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }
        {
            size_t start = i;
            size_t end;

            while (i < len && !isspace((unsigned char)str[i])) {
                i++;
            }
            end = i - 1;
            str[start] = (char)toupper((unsigned char)str[start]);
            str[end] = (char)toupper((unsigned char)str[end]);
        }
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char *newline;

    if (printf("Enter a string: ") < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    capitalize_first_last(buffer);

    if (printf("Result: %s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}