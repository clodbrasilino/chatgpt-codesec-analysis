#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(int character)
{
    return character != EOF && isdigit((unsigned char)character) != 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(line);
                return 1;
            }

            char *new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                free(line);
                return 1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(line);
        return 1;
    }

    while (length > 0 && line[length - 1] == '\r') {
        --length;
    }

    bool result = length > 0 &&
                  ends_with_number((unsigned char)line[length - 1]);

    free(line);

    return puts(result ? "true" : "false") == EOF ? 1 : 0;
}