#include <stdio.h>
#include <stdlib.h>

static void print_ascii_values(const char *string)
{
    if (string == NULL) {
        return;
    }

    while (*string != '\0') {
        if (printf("%u\n", (unsigned int)(unsigned char)*string) < 0) {
            return;
        }
        ++string;
    }
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *temporary;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            temporary = realloc(string, new_capacity);
            if (temporary == NULL) {
                free(string);
                return 1;
            }

            string = temporary;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (ferror(stdin)) {
        perror("fgetc");
        free(string);
        return 1;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return 1;
        }
    }

    string[length] = '\0';
    print_ascii_values(string);
    free(string);

    return ferror(stdout) ? 1 : 0;
}