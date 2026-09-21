#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DATE_LEN 10U
#define DATE_BUF_SIZE 11U
#define INPUT_BUF_SIZE (DATE_BUF_SIZE + 2U)
#define YEAR_BUF_SIZE 5U
#define MONTH_BUF_SIZE 3U
#define DAY_BUF_SIZE 3U

static int is_valid_format(const char *date)
{
    size_t i;

    if (date == NULL) {
        return 0;
    }

    if (strnlen(date, DATE_BUF_SIZE) != DATE_LEN) {
        return 0;
    }

    for (i = 0U; i < DATE_LEN; i++) {
        if ((i == 4U) || (i == 7U)) {
            if (date[i] != '-') {
                return 0;
            }
        } else {
            if (isdigit((unsigned char)date[i]) == 0) {
                return 0;
            }
        }
    }

    return 1;
}

static int is_valid_date(int year, int month, int day)
{
    static const int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int max_day;

    if ((year < 1) || (year > 9999)) {
        return 0;
    }

    if ((month < 1) || (month > 12)) {
        return 0;
    }

    max_day = days_in_month[month - 1];

    if (month == 2) {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
            max_day = 29;
        }
    }

    if ((day < 1) || (day > max_day)) {
        return 0;
    }

    return 1;
}

static int parse_date_fields(const char *input, int *year, int *month, int *day)
{
    char year_buf[YEAR_BUF_SIZE];
    char month_buf[MONTH_BUF_SIZE];
    char day_buf[DAY_BUF_SIZE];
    char *endptr = NULL;
    long value;

    if ((input == NULL) || (year == NULL) || (month == NULL) || (day == NULL)) {
        return -1;
    }

    if (strnlen(input, DATE_BUF_SIZE) != DATE_LEN) {
        return -1;
    }

    memset(year_buf, 0, sizeof(year_buf));
    memset(month_buf, 0, sizeof(month_buf));
    memset(day_buf, 0, sizeof(day_buf));

    memcpy(year_buf, &input[0], sizeof(year_buf) - 1U);
    memcpy(month_buf, &input[5], sizeof(month_buf) - 1U);
    memcpy(day_buf, &input[8], sizeof(day_buf) - 1U);

    year_buf[sizeof(year_buf) - 1U] = '\0';
    month_buf[sizeof(month_buf) - 1U] = '\0';
    day_buf[sizeof(day_buf) - 1U] = '\0';

    value = strtol(year_buf, &endptr, 10);
    if ((endptr == year_buf) || (*endptr != '\0') || (value < 0L) || (value > 9999L)) {
        return -1;
    }
    *year = (int)value;

    endptr = NULL;
    value = strtol(month_buf, &endptr, 10);
    if ((endptr == month_buf) || (*endptr != '\0') || (value < 0L) || (value > 99L)) {
        return -1;
    }
    *month = (int)value;

    endptr = NULL;
    value = strtol(day_buf, &endptr, 10);
    if ((endptr == day_buf) || (*endptr != '\0') || (value < 0L) || (value > 99L)) {
        return -1;
    }
    *day = (int)value;

    return 0;
}

static int convert_date(const char *input, char *output, size_t output_size)
{
    int year = 0;
    int month = 0;
    int day = 0;
    int written;

    if ((input == NULL) || (output == NULL) || (output_size < DATE_BUF_SIZE)) {
        return -1;
    }

    if (is_valid_format(input) == 0) {
        return -1;
    }

    if (parse_date_fields(input, &year, &month, &day) != 0) {
        return -1;
    }

    if (is_valid_date(year, month, day) == 0) {
        return -1;
    }

    written = snprintf(output, output_size, "%02d-%02d-%04d", day, month, year);

    if ((written < 0) || ((size_t)written >= output_size)) {
        return -1;
    }

    return 0;
}

static int read_input_line(char *buffer, size_t buffer_size)
{
    size_t len;

    if ((buffer == NULL) || (buffer_size < 2U)) {
        return -1;
    }

    if (fgets(buffer, (int)buffer_size, stdin) == NULL) {
        return -1;
    }

    buffer[buffer_size - 1U] = '\0';

    len = strnlen(buffer, buffer_size);

    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    } else if (len == (buffer_size - 1U)) {
        int ch;
        do {
            ch = getchar();
        } while ((ch != '\n') && (ch != EOF));
    }

    return 0;
}

int main(void)
{
    char input[INPUT_BUF_SIZE];
    char output[DATE_BUF_SIZE];

    memset(input, 0, sizeof(input));
    memset(output, 0, sizeof(output));

    printf("Enter date (yyyy-mm-dd): ");

    if (read_input_line(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (convert_date(input, output, sizeof(output)) != 0) {
        fprintf(stderr, "Invalid date format or value\n");
        return EXIT_FAILURE;
    }

    printf("Converted date: %s\n", output);

    return EXIT_SUCCESS;
}