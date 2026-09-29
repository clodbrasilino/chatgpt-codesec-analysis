#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256

int first_repeated_char(const char *str)
{
    bool seen[UCHAR_MAX + 1] = { false };
    size_t i;

    if (str == NULL) {
        return -1;
    }

    for (i = 0; i < BUFFER_SIZE && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return (int)c;
        }
        seen[c] = true;
    }

    return -1;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0;

    do {
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < (size_t)INT_MAX);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    int result;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return 1;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        flush_stdin();
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = first_repeated_char(buffer);

    if (result == -1) {
        printf("No repeated character found\n");
    } else {
        printf("First repeated character: %c\n", (char)result);
    }

    return 0;
}