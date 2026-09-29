#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define DATE_LENGTH 10
#define DATE_BUFFER_SIZE 12

static bool is_valid_date(int year, int month, int day)
{
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }
    
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        days_in_month[1] = 29;
    }
    
    return day <= days_in_month[month - 1];
}

bool convert_date_format(const char *input_date, char *output_date, size_t output_size)
{
    int year, month, day;
    size_t input_len;
    
    if (input_date == NULL || output_date == NULL || output_size < DATE_BUFFER_SIZE)
    {
        return false;
    }
    
    input_len = strnlen(input_date, DATE_BUFFER_SIZE);
    if (input_len != DATE_LENGTH)
    {
        return false;
    }
    
    if (sscanf(input_date, "%4d-%2d-%2d", &year, &month, &day) != 3)
    {
        return false;
    }
    
    if (input_date[4] != '-' || input_date[7] != '-')
    {
        return false;
    }
    
    if (!is_valid_date(year, month, day))
    {
        return false;
    }
    
    if (snprintf(output_date, output_size, "%02d-%02d-%04d", day, month, year) < 0)
    {
        return false;
    }
    
    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_date[DATE_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output_date[DATE_BUFFER_SIZE];
    
    printf("Enter date in yyyy-mm-dd format: ");
    
    if (fgets(input_date, sizeof(input_date), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strnlen(input_date, sizeof(input_date));
    if (len > 0 && input_date[len - 1] == '\n')
    {
        input_date[len - 1] = '\0';
    }
    
    if (convert_date_format(input_date, output_date, sizeof(output_date)))
    {
        printf("Converted date: %s\n", output_date);
    }
    else
    {
        fprintf(stderr, "Invalid date format\n");
        return 1;
    }
    
    return 0;
}