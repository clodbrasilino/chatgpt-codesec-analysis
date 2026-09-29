#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>

#define BUFFER_SIZE 256

int find_first_repeated_char(const char *str, size_t max_len, char *result)
{
    unsigned char seen[UCHAR_MAX + 1] = {0};
    size_t i;

    if (str == NULL || result == NULL || max_len == 0) {
        return -1;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] != 0) {
            *result = str[i];
            return 0;
        }
        seen[c] = 1;
    }

    return 1;
}

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0;
    const size_t guard_limit = (size_t)-1;

    while (guard < guard_limit) {
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        guard++;
    }
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    char repeated = '\0';
    int status;
    size_t len;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");
    if (len >= sizeof(buffer)) {
        len = sizeof(buffer) - 1;
    }
    buffer[len] = '\0';

    if (len == sizeof(buffer) - 1) {
        discard_remaining_input();
    }

    status = find_first_repeated_char(buffer, sizeof(buffer), &repeated);

    if (status == 0) {
        printf("First repeated character: %c\n", repeated);
    } else if (status == 1) {
        printf("No repeated character found\n");
    } else {
        fprintf(stderr, "Invalid input to function\n");
        return 1;
    }

    return 0;
}