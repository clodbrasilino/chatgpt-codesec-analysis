#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define BUFFER_SIZE 256

size_t count_characters(const char *str);
void strip_newline(char *str);
static void flush_stdin(void);

size_t count_characters(const char *str)
{
    size_t count = 0;

    if (str == NULL)
    {
        return 0;
    }

    while (count < BUFFER_SIZE && str[count] != '\0')
    {
        count++;
    }

    return count;
}

void strip_newline(char *str)
{
    size_t i = 0;

    if (str == NULL)
    {
        return;
    }

    while (i < BUFFER_SIZE && str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            return;
        }
        i++;
    }
}

static void flush_stdin(void)
{
    size_t guard = 0;
    const size_t max_flush = 1024 * 1024;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    while (guard < max_flush)
    {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        guard++;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t length;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fflush(stdout) != 0)
    {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (memchr(buffer, '\n', sizeof(buffer)) == NULL)
    {
        flush_stdin();
    }

    strip_newline(buffer);

    length = count_characters(buffer);

    printf("Total characters: %zu\n", length);

    return 0;
}