#include <stdio.h>
#include <string.h>

static void remove_character(char *string, char character)
{
    char *source;
    char *destination;

    if (string == NULL) {
        return;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        if (*source != character) {
            *destination++ = *source;
        }
        ++source;
    }

    *destination = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char character_line[1024];
    size_t length;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    length = strcspn(string, "\n");
    if (string[length] == '\n') {
        string[length] = '\0';
    } else if (!feof(stdin)) {
        int input;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((input = fgetc(stdin)) != '\n' && input != EOF) {
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    if (fgets(character_line, sizeof character_line, stdin) == NULL) {
        return 1;
    }

    if (character_line[0] == '\n' || character_line[0] == '\0') {
        return 1;
    }

    length = strcspn(character_line, "\n");
    if (character_line[length] != '\n' && !feof(stdin)) {
        int input;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((input = fgetc(stdin)) != '\n' && input != EOF) {
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    remove_character(string, character_line[0]);

    if (puts(string) == EOF) {
        return 1;
    }

    return 0;
}