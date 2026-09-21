#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

long long count_integral_coordinates(long long side_length)
{
    if (side_length < 0)
    {
        return -1;
    }

    if (side_length == 0)
    {
        return 1;
    }

    if (side_length > (LLONG_MAX - 1) / (side_length + 1))
    {
        return -1;
    }

    long long points_per_side = side_length + 1;
    return points_per_side * points_per_side;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *end_ptr = NULL;
    long long side_length = 0;
    long long result = 0;

    printf("Enter the side length of the square: ");

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t input_length = strnlen(input_buffer, sizeof(input_buffer));
    if (input_length == sizeof(input_buffer) && !feof(stdin))
    {
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (input_length > 0 && input_buffer[input_length - 1] == '\n')
    {
        input_buffer[input_length - 1] = '\0';
    }

    errno = 0;
    side_length = strtoll(input_buffer, &end_ptr, 10);

    if (errno == ERANGE)
    {
        fprintf(stderr, "Input value out of range\n");
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer)
    {
        fprintf(stderr, "Invalid input: not a number\n");
        return EXIT_FAILURE;
    }

    while (*end_ptr != '\0' && isspace((unsigned char)*end_ptr))
    {
        end_ptr++;
    }

    if (*end_ptr != '\0')
    {
        fprintf(stderr, "Invalid input: trailing characters\n");
        return EXIT_FAILURE;
    }

    if (side_length < 0)
    {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }

    result = count_integral_coordinates(side_length);

    if (result < 0)
    {
        fprintf(stderr, "Result would overflow\n");
        return EXIT_FAILURE;
    }

    printf("Number of integral coordinates: %lld\n", result);

    return EXIT_SUCCESS;
}