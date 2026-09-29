#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MAX_FLUSH (BUFFER_SIZE * 16)

void remove_char(char *str, size_t str_size, char ch);
static void flush_stdin(void);
static int read_line(char *buffer, size_t size);
static int read_char(char *out);

void remove_char(char *str, size_t str_size, char ch)
{
    size_t i;
    size_t j;

    if (str == NULL || str_size == 0) {
        return;
    }

    j = 0;
    for (i = 0; i < str_size && str[i] != '\0'; i++) {
        if (str[i] != ch) {
            str[j] = str[i];
            j++;
        }
    }

    if (j < str_size) {
        str[j] = '\0';
    } else {
        str[str_size - 1] = '\0';
    }
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
    } while (discard != '\n' && discard != EOF && count < (size_t)MAX_FLUSH);
}

static int read_line(char *buffer, size_t size)
{
    size_t len;
    int newline_found;

    if (buffer == NULL || size == 0) {
        return -1;
    }

    if (size > (size_t)INT_MAX) {
        size = (size_t)INT_MAX;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strcspn(buffer, "\n");
    if (len >= size) {
        len = size - 1;
    }
    newline_found = (buffer[len] == '\n');
    buffer[len] = '\0';

    if (!newline_found) {
        flush_stdin();
    }

    return 0;
}

static int read_char(char *out)
{
    int input;

    if (out == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    input = getchar();
    if (input == EOF) {
        return -1;
    }

    if (input != '\n') {
        flush_stdin();
    }

    *out = (char)input;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char target;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    printf("Enter the character to remove: ");
    if (read_char(&target) != 0) {
        fprintf(stderr, "Error reading character input\n");
        return EXIT_FAILURE;
    }

    remove_char(buffer, sizeof(buffer), target);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}