#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool convert_date_format(const char *input_date, char *output_date, size_t output_size)
{
    int year, month, day;
    char extra;
    
    if (input_date == NULL || output_date == NULL || output_size < 11)
    {
        return false;
    }
    
    if (strlen(input_date) != 10)
    {
        return false;
    }
    
    if (sscanf(input_date, "%4d-%2d-%2d%c", &year, &month, &day, &extra) != 3)
    {
        return false;
    }
    
    if (input_date[4] != '-' || input_date[7] != '-')
    {
        return false;
    }
    
    if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
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
    char input_date[11];
    char output_date[11];
    
    printf("Enter date in yyyy-mm-dd format: ");
    
    if (fgets(input_date, sizeof(input_date), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    size_t len = strlen(input_date);
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