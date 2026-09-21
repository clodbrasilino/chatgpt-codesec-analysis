#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 64

static int has_31_days(const char *month)
{
    static const char *months_with_31[] = {
        "January", "March", "May", "July",
        "August", "October", "December"
    };
    size_t count = sizeof(months_with_31) / sizeof(months_with_31[0]);
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (strcmp(month, months_with_31[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static void discard_remaining_input(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int main(void)
{
    char buffer[BUFFER_SIZE];
    size_t len;

    printf("Enter month name: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    }

    if (len == sizeof(buffer) - 1 && strchr(buffer, '\n') == NULL) {
        discard_remaining_input();
    }

    if (len == 0) {
        fprintf(stderr, "No input provided\n");
        return EXIT_FAILURE;
    }

    if (has_31_days(buffer)) {
        printf("%s has 31 days\n", buffer);
    } else {
        printf("%s does not have 31 days\n", buffer);
    }

    return EXIT_SUCCESS;
}