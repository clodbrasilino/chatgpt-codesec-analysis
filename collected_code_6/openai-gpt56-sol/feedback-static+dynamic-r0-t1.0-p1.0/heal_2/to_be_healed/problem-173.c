#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static void remove_non_alphanumeric(char *str)
{
    if (str == NULL) {
        return;
    }

    unsigned char *read_ptr = (unsigned char *)str;
    char *write_ptr = str;

    while (*read_ptr != '\0') {
        if (isalnum(*read_ptr) != 0) {
            *write_ptr++ = (char)*read_ptr;
        }
        ++read_ptr;
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return 1;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) != 0) {
        free(input);
        return 1;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return 0;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = length + 1;
        char *resized = realloc(input, new_capacity);

        if (resized == NULL) {
            free(input);
            return 1;
        }

        input = resized;
        /* Possible weaknesses found:
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         */
        capacity = new_capacity;
    }

    input[length] = '\0';
    remove_non_alphanumeric(input);

    if (puts(input) == EOF) {
        free(input);
        return 1;
    }

    free(input);
    return 0;
}