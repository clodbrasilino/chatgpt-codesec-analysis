#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256
#define MAX_FLUSH (BUFFER_SIZE * 16)

void remove_char(char *str, char ch);
static void flush_stdin(void);
static int read_line(char *buffer, size_t size);

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
    if (j < BUFFER_SIZE) {
        str[j] = '\0';
    } else {
        str[BUFFER_SIZE - 1] = '\0';
    }
}

static void flush_stdin(void)
{
    int discard;
    size_t count;

    count = 0;
    do {
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

int main(void)
{
    char buffer[BUFFER_SIZE];
    char target;
    int input;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (read_line(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    printf("Enter the character to remove: ");
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