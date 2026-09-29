#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void remove_char(char *str, char ch)
{
    size_t i;
    size_t j;

    if (str == NULL) {
        return;
    }

    j = 0;
    for (i = 0; i < BUFFER_SIZE && str[i] != '\0'; i++) {
        if (str[i] != ch) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

static void flush_stdin(void)
{
    int discard;
    size_t count;

    count = 0;
    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        discard = getchar();
        count++;
    } while (discard != '\n' && discard != EOF && count < BUFFER_SIZE * 16);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char target;
    int input;
    size_t len;
    int newline_found;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");
    if (len >= sizeof(buffer)) {
        len = sizeof(buffer) - 1;
    }
    newline_found = (buffer[len] == '\n');
    buffer[len] = '\0';

    if (!newline_found) {
        flush_stdin();
    }

    printf("Enter the character to remove: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = getchar();
    if (input == EOF) {
        fprintf(stderr, "Error reading character input\n");
        return EXIT_FAILURE;
    }
    target = (char)input;

    remove_char(buffer, target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}