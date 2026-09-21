#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

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

static bool read_line(char *buffer, size_t size)
{
    if (buffer == NULL || size == 0)
        return false;
    
    if (fgets(buffer, size, stdin) == NULL)
        return false;
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    
    if (len == 0)
        return false;
    
    if (buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        return true;
    }
    
    if (len == size - 1)
    {
        int c;
        int count = 0;
        const int max_discard = 4096;
        
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF)
        {
            if (++count >= max_discard)
            {
                return false;
            }
        }
        
        return false;
    }
    
    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *end_ptr;
    long year_value;
    int result;
    
    if (!read_line(input_buffer, sizeof(input_buffer)))
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
    
    while (*end_ptr == ' ' || *end_ptr == '\t' || *end_ptr == '\r')
    {
        end_ptr++;
    }
    
    if (*end_ptr != '\0')
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