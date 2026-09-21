#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 256

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i = 0;

    while (i < max_len && str[i] != '\0') {
        i++;
    }

    return i;
}

void toggle_case(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return;
    }

    len = bounded_strlen(str, max_len);
    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isupper(c)) {
            str[i] = (char)tolower(c);
        } else if (islower(c)) {
            str[i] = (char)toupper(c);
        }
    }
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    toggle_case(buffer, sizeof(buffer));

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}