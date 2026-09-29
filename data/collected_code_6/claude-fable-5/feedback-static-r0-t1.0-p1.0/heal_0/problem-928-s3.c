#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int convert_date(const char *input, char *output, size_t output_size)
{
    unsigned int year;
    unsigned int month;
    unsigned int day;
    size_t i;
    int written;

    if (input == NULL || output == NULL) {
        return -1;
    }

    if (output_size < 11U) {
        return -1;
    }

    if (strlen(input) != 10U) {
        return -1;
    }

    for (i = 0U; i < 10U; i++) {
        if (i == 4U || i == 7U) {
            if (input[i] != '-') {
                return -1;
            }
        } else {
            if (!isdigit((unsigned char)input[i])) {
                return -1;
            }
        }
    }

    if (sscanf(input, "%4u-%2u-%2u", &year, &month, &day) != 3) {
        return -1;
    }

    if (year < 1U || year > 9999U) {
        return -1;
    }

    if (month < 1U || month > 12U) {
        return -1;
    }

    if (day < 1U || day > 31U) {
        return -1;
    }

    written = snprintf(output, output_size, "%02u-%02u-%04u", day, month, year);
    if (written < 0 || (size_t)written >= output_size) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[32];
    char output[16];

    printf("Enter date (yyyy-mm-dd): ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (convert_date(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid date format\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    return EXIT_SUCCESS;
}