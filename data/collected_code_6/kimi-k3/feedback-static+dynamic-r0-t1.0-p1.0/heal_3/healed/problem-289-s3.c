#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 32

static int is_leap_year(int year)
{
    if (year < 0)
    {
        return -1;
    }
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int calculate_odd_days(int year)
{
    int leap_check = is_leap_year(year);
    if (leap_check < 0)
    {
        return -1;
    }
    return leap_check ? 2 : 1;
}

int main(void)
{
    char input_buffer[INPUT_BUFFER_SIZE];
    char *end_ptr;
    long year_long;
    int year;
    int odd_days;
    size_t len;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        return EXIT_FAILURE;
    }

    input_buffer[sizeof(input_buffer) - 1] = '\0';

    len = strnlen(input_buffer, sizeof(input_buffer));
    if (len == 0 || len >= sizeof(input_buffer))
    {
        return EXIT_FAILURE;
    }

    if (len == sizeof(input_buffer) - 1 && input_buffer[len - 1] != '\n')
    {
        return EXIT_FAILURE;
    }

    errno = 0;
    year_long = strtol(input_buffer, &end_ptr, 10);

    if (errno != 0 || end_ptr == input_buffer || year_long < 0 || year_long > INT_MAX)
    {
        return EXIT_FAILURE;
    }

    if (*end_ptr != '\0' && *end_ptr != '\n')
    {
        return EXIT_FAILURE;
    }

    year = (int)year_long;
    odd_days = calculate_odd_days(year);

    if (odd_days < 0)
    {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", odd_days) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}