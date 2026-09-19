#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void capitalize_first_last(char *str)
{
    size_t i;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    size_t start;
    /* Possible weaknesses found:
     *  The scope of the variable 'end' can be reduced. [variableScope]
     */
    size_t end;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    i = 0;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }

        if (i >= len) {
            break;
        }

        start = i;

        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }

        end = i - 1;

        str[start] = (char)toupper((unsigned char)str[start]);
        str[end] = (char)toupper((unsigned char)str[end]);
    }
}

int main(void)
{
    const char *input = "hello world this is a test";
    size_t buf_size;
    char *buffer;

    buf_size = strlen(input) + 1;
    buffer = malloc(buf_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, input, buf_size);

    capitalize_first_last(buffer);

    if (printf("Original: %s\n", input) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    if (printf("Modified: %s\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    return EXIT_SUCCESS;
}