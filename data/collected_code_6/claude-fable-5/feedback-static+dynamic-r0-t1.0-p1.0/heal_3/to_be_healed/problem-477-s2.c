#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 256

void string_to_lower(char *str)
{
    size_t i;

    if (str == NULL) {
        return;
    }

    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

static void flush_stdin(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];

    printf("Enter a string: ");

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        flush_stdin();
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    string_to_lower(buffer);

    printf("Lowercase: %s\n", buffer);

    return EXIT_SUCCESS;
}