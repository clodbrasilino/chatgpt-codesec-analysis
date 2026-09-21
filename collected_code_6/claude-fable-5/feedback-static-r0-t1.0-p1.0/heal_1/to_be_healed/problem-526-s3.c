#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void capitalize_first_last(char *str)
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *newline;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

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