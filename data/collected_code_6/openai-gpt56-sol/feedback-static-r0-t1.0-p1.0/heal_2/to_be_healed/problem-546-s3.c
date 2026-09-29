#include <stdio.h>
#include <stdlib.h>

const char *find_last_char(const char *str, int ch)
{
    const char *last = NULL;
    unsigned char target = (unsigned char)ch;

    if (str == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*str == target) {
            last = str;
        }
    } while (*str++ != '\0');

    return last;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;
    int current;
    const char *result;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((current = getchar()) != '\n' && current != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Input is too large.\n", stderr);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)current;
    }

    if (current == EOF && length == 0) {
        free(input);
        fputs("Failed to read the string.\n", stderr);
        return 1;
    }

    if (length + 1 >= capacity) {
        size_t new_capacity = capacity == 0 ? 2 : capacity + 1;
        char *new_input = realloc(input, new_capacity);

        if (new_input == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return 1;
        }

        input = new_input;
        /* Possible weaknesses found:
         *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'capacity' is never read [deadcode.DeadStores]
         */
        capacity = new_capacity;
    }

    input[length++] = '\n';
    input[length] = '\0';

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = getchar();
    if (ch == EOF) {
        free(input);
        fputs("Failed to read the character.\n", stderr);
        return 1;
    }

    result = find_last_char(input, ch);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    free(input);
    return 0;
}