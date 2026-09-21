#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#define FIRST_YEAR_DOG_YEARS 15
#define SECOND_YEAR_DOG_YEARS 9
#define SUBSEQUENT_YEAR_DOG_YEARS 5
#define INPUT_BUFFER_SIZE 64

int calculate_dog_years(int human_years)
{
    if (human_years < 0) {
        return -1;
    }
    
    if (human_years == 0) {
        return 0;
    }
    
    if (human_years == 1) {
        return FIRST_YEAR_DOG_YEARS;
    }
    
    if (human_years == 2) {
        return FIRST_YEAR_DOG_YEARS + SECOND_YEAR_DOG_YEARS;
    }
    
    if (human_years > (INT_MAX - FIRST_YEAR_DOG_YEARS - SECOND_YEAR_DOG_YEARS) / SUBSEQUENT_YEAR_DOG_YEARS + 2) {
        return -1;
    }
    
    return FIRST_YEAR_DOG_YEARS + SECOND_YEAR_DOG_YEARS + 
           (human_years - 2) * SUBSEQUENT_YEAR_DOG_YEARS;
}

int main(void)
{
    char input_buffer[INPUT_BUFFER_SIZE];
    char *end_ptr;
    long human_years_long;
    int human_years;
    int dog_years;
    size_t input_length;
    int input_too_long;
    
    printf("Enter dog's age in human years: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    input_buffer[sizeof(input_buffer) - 1] = '\0';
    
    input_length = strnlen(input_buffer, sizeof(input_buffer));
    
    if (input_length == 0) {
        fprintf(stderr, "No input provided\n");
        return EXIT_FAILURE;
    }
    
    input_too_long = 0;
    
    if (input_buffer[input_length - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            if (c != EOF) {
                input_too_long = 1;
            }
        }
        if (input_too_long || input_length == sizeof(input_buffer) - 1) {
            fprintf(stderr, "Input too long\n");
            return EXIT_FAILURE;
        }
    } else {
        input_buffer[input_length - 1] = '\0';
        input_length--;
    }
    
    if (input_length == 0) {
        fprintf(stderr, "No input provided\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    human_years_long = strtol(input_buffer, &end_ptr, 10);
    
    if (errno == ERANGE) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }
    
    if (errno != 0) {
        fprintf(stderr, "Error converting input\n");
        return EXIT_FAILURE;
    }
    
    if (end_ptr == input_buffer) {
        fprintf(stderr, "No valid number entered\n");
        return EXIT_FAILURE;
    }
    
    if (*end_ptr != '\0') {
        fprintf(stderr, "Invalid characters in input\n");
        return EXIT_FAILURE;
    }
    
    if (human_years_long < 0 || human_years_long > INT_MAX) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }
    
    human_years = (int)human_years_long;
    
    dog_years = calculate_dog_years(human_years);
    
    if (dog_years < 0) {
        fprintf(stderr, "Error calculating dog years\n");
        return EXIT_FAILURE;
    }
    
    printf("Dog's age in dog years: %d\n", dog_years);
    
    return EXIT_SUCCESS;
}