#include <stdio.h>
#include <string.h>

#define DATE_LENGTH 10
#define BUFFER_SIZE 32

int convert_date(const char *input, char *output, size_t output_size)
{
    int year;
    int month;
    int day;
    char extra;

    if (input == NULL || output == NULL || output_size < DATE_LENGTH + 1) {
        return -1;
    }

    if (strlen(input) != DATE_LENGTH ||
        sscanf(input, "%4d-%2d-%2d%c", &year, &month, &day, &extra) != 3) {
        return -1;
    }

    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31) {
        return -1;
    }

    if (snprintf(output, output_size, "%02d-%02d-%04d", day, month, year) != DATE_LENGTH) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[BUFFER_SIZE];
    char output[DATE_LENGTH + 1];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\r\n")] = '\0';

    if (convert_date(input, output, sizeof(output)) != 0) {
        fputs("Invalid date\n", stderr);
        return 1;
    }

    if (printf("%s\n", output) < 0) {
        return 1;
    }

    return 0;
}