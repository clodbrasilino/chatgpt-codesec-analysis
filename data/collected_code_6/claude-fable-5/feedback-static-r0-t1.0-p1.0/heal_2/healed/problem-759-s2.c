#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

bool is_decimal_with_precision_two(const char *str);
static bool read_line(char *buffer, size_t size);

bool is_decimal_with_precision_two(const char *str)
{
    size_t i = 0;
    size_t digits_before = 0;
    size_t digits_after = 0;

    if (str == NULL || str[0] == '\0') {
        return false;
    }

    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
        digits_before++;
        i++;
    }

    if (digits_before == 0) {
        return false;
    }

    if (str[i] != '.') {
        return false;
    }
    i++;

    while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
        digits_after++;
        i++;
    }

    if (str[i] != '\0') {
        return false;
    }

    return digits_after == 2;
}

static bool read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size < 2) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return false;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        size_t discarded = 0;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            if (discarded < (size_t)-1) {
                discarded++;
            }
        }
        fprintf(stderr, "Input too long\n");
        return false;
    }

    buffer[strcspn(buffer, "\r\n")] = '\0';
    return true;
}

int main(void)
{
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));

    if (!read_line(buffer, sizeof(buffer))) {
        return EXIT_FAILURE;
    }

    if (is_decimal_with_precision_two(buffer)) {
        printf("Valid decimal with precision 2\n");
    } else {
        printf("Invalid decimal with precision 2\n");
    }

    return EXIT_SUCCESS;
}