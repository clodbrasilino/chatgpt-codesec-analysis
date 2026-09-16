#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int calculate_dog_age(int human_years, int *dog_years)
{
    if (dog_years == NULL)
    {
        return -1;
    }

    if (human_years < 0)
    {
        return -1;
    }

    if (human_years <= 2)
    {
        if (human_years > INT_MAX / 15)
        {
            return -1;
        }
        *dog_years = human_years * 15;
    }
    else
    {
        if (human_years > (INT_MAX - 24) / 4 + 2)
        {
            return -1;
        }
        *dog_years = 24 + (human_years - 2) * 4;
    }

    return 0;
}

int main(void)
{
    char input_buffer[128];
    char *end_ptr;
    long human_years_long;
    int human_years;
    int dog_years;
    int result;

    printf("Enter dog's age in human years: ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    human_years_long = strtol(input_buffer, &end_ptr, 10);

    if (errno == ERANGE || human_years_long > INT_MAX || human_years_long < INT_MIN)
    {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer)
    {
        fprintf(stderr, "Invalid input: not a number.\n");
        return EXIT_FAILURE;
    }

    if (*end_ptr != '\n' && *end_ptr != '\0')
    {
        fprintf(stderr, "Invalid input: trailing characters.\n");
        return EXIT_FAILURE;
    }

    human_years = (int)human_years_long;

    result = calculate_dog_age(human_years, &dog_years);

    if (result != 0)
    {
        fprintf(stderr, "Error calculating dog age.\n");
        return EXIT_FAILURE;
    }

    printf("Dog's age in dog years: %d\n", dog_years);

    return EXIT_SUCCESS;
}