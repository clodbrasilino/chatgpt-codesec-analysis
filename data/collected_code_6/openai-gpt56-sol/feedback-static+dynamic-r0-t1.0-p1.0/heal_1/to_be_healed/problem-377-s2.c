#include <stdio.h>
#include <string.h>

void remove_character(char *string, char character)
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
    int input;
    int character;

    if (fgets(string, sizeof string, stdin) == NULL) {
        return 1;
    }

    string[strcspn(string, "\n")] = '\0';

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = getchar();
    if (character == EOF) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((input = getchar()) != '\n' && input != EOF) {
    }

    remove_character(string, (char)character);
    puts(string);

    if (ferror(stdin) || ferror(stdout)) {
        return 1;
    }

    return 0;
}