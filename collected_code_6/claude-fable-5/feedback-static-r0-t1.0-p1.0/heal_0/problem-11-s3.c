#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_first_last(char *str, char ch)
{
    size_t len;
    char *first;
    char *last;

    if (str == NULL) {
        return;
    }

    len = strlen(str);
    if (len == 0U) {
        return;
    }

    first = strchr(str, (int)ch);
    if (first == NULL) {
        return;
    }

    last = strrchr(str, (int)ch);

    if (last != NULL && last != first) {
        memmove(last, last + 1, strlen(last + 1) + 1U);
    }

    memmove(first, first + 1, strlen(first + 1) + 1U);
}

int main(void)
{
    char buffer[256];
    char ch;
    int c;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input string\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Enter a character to remove: ");
    c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error reading character\n");
        return EXIT_FAILURE;
    }
    ch = (char)c;

    remove_first_last(buffer, ch);

    printf("Result: %s\n", buffer);

    return EXIT_SUCCESS;
}