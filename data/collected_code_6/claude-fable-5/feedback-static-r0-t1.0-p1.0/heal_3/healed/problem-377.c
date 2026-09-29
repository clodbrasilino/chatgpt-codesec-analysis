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
    for (i = 0; str[i] != '\0'; i++) {
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

    do {
        discard = getchar();
    } while (discard != '\n' && discard != EOF);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char target;
    int input;
    size_t len;
    int newline_found;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");
    newline_found = (buffer[len] == '\n');
    buffer[len] = '\0';

    if (!newline_found) {
        flush_stdin();
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