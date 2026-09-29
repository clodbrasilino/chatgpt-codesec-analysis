#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 64
#define FLUSH_LIMIT 4096

int has_31_days(const char *month)
{
    static const char *const months_with_31[] = {
        "January", "March", "May", "July",
        "August", "October", "December"
    };
    size_t count = sizeof(months_with_31) / sizeof(months_with_31[0]);
    size_t i;

    if (month == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (strncmp(month, months_with_31[i], BUFFER_SIZE) == 0) {
            return 1;
        }
    }
    return 0;
}

static void flush_stdin(void)
{
    int ch;
    size_t guard = 0;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        guard++;
    } while (ch != '\n' && ch != EOF && guard < FLUSH_LIMIT);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE] = {0};
    size_t len;

    printf("Enter month name: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == sizeof(buffer) - 1) {
        flush_stdin();
    }

    if (has_31_days(buffer)) {
        printf("%s has 31 days\n", buffer);
    } else {
        printf("%s does not have 31 days\n", buffer);
    }

    return EXIT_SUCCESS;
}