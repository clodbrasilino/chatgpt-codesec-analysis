#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void capitalize_first_last(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return;
    }

    len = strnlen(str, max_len);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
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

    capitalize_first_last(buffer, sizeof(buffer));

    if (printf("Result: %s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}