#include <stdio.h>
#include <stdlib.h>

static void remove_odd_characters(char *string)
{
    char *read_ptr;
    char *write_ptr;

    if (string == NULL) {
        return;
    }

    read_ptr = string;
    write_ptr = string;

    while (*read_ptr != '\0') {
        *write_ptr++ = *read_ptr++;

        if (*read_ptr != '\0') {
            ++read_ptr;
        }
    }

    *write_ptr = '\0';
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;
            char *resized;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            resized = realloc(string, new_capacity);
            if (resized == NULL) {
                free(string);
                return 1;
            }

            string = resized;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin) != 0) {
        free(string);
        return 1;
    }

    if (length == 0U && character == EOF) {
        free(string);
        return 0;
    }

    if (length + 1U >= capacity) {
        char *resized = realloc(string, length + 1U);

        if (resized == NULL) {
            free(string);
            return 1;
        }

        string = resized;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = length + 1U;
    }

    string[length] = '\0';
    remove_odd_characters(string);

    if (puts(string) == EOF) {
        free(string);
        return 1;
    }

    free(string);
    return 0;
}