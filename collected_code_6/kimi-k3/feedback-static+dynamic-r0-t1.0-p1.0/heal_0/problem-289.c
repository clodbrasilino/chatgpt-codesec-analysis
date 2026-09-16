#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static bool is_leap_year(int year)
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    return (year % 4 == 0);
}

static int calculate_odd_days(int year)
{
    if (year < 1)
        return -1;
    
    if (year == 1)
        return 1;
    
    int previous_year = year - 1;
    int leap_years = (previous_year / 4) - (previous_year / 100) + (previous_year / 400);
    int regular_years = previous_year - leap_years;
    
    int odd_days = (leap_years * 2 + regular_years) % 7;
    
    return odd_days;
}

int main(void)
{
    char input_buffer[32];
    char *end_ptr;
    long year_value;
    int result;
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    year_value = strtol(input_buffer, &end_ptr, 10);
    
    if (errno == ERANGE || year_value > INT_MAX || year_value < 1)
    {
        return EXIT_FAILURE;
    }
    
    if (end_ptr == input_buffer)
    {
        return EXIT_FAILURE;
    }
    
    result = calculate_odd_days((int)year_value);
    
    if (result < 0)
    {
        return EXIT_FAILURE;
    }
    
    if (printf("%d\n", result) < 0)
    {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}