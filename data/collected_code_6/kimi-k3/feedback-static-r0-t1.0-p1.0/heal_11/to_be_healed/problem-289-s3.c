#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[64];
    char *end_ptr;
    long year_long;
    int year;
    int odd_days;
    size_t len = 0;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        return EXIT_FAILURE;
    }

    while (len < sizeof(input_buffer) - 1 && input_buffer[len] != '\0')
    {
        len++;
    }

    if (len > 0 && input_buffer[len - 1] == '\n')
    {
        input_buffer[len - 1] = '\0';
    }
    else if (len == sizeof(input_buffer) - 1)
    {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != EOF && ch != '\n')
        {
        }
        return EXIT_FAILURE;
    }

    errno = 0;
    year_long = strtol(input_buffer, &end_ptr, 10);

    if (errno != 0 || end_ptr == input_buffer || *end_ptr != '\0' || year_long < 0 || year_long > INT_MAX)
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