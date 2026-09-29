#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int left_rotate_string(char *str, size_t positions, size_t buffer_size)
{
    size_t len;
    size_t i;
    size_t j;
    char *temp;

    if (str == NULL || buffer_size == 0)
    {
        return -1;
    }

    len = strnlen(str, buffer_size);
    if (len == buffer_size && str[len - 1] != '\0')
    {
        return -1;
    }

    if (len == 0)
    {
        return 0;
    }

    positions = positions % len;
    if (positions == 0)
    {
        return 0;
    }

    if (positions > SIZE_MAX / sizeof(char))
    {
        return -1;
    }

    temp = (char *)malloc(positions * sizeof(char));
    if (temp == NULL)
    {
        return -1;
    }

    for (i = 0; i < positions; i++)
    {
        temp[i] = str[i];
    }

    for (i = positions, j = 0; i < len; i++, j++)
    {
        str[j] = str[i];
    }

    for (i = 0; i < positions; i++)
    {
        str[len - positions + i] = temp[i];
    }

    free(temp);
    temp = NULL;

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *input;
    size_t positions;
    int result;
    char *endptr;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pos_buffer[32];
    unsigned long temp_pos;

    printf("Enter a string: ");
    input = fgets(buffer, sizeof(buffer), stdin);
    if (input == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Enter number of positions to rotate: ");
    if (fgets(pos_buffer, sizeof(pos_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading positions\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp_pos = strtoul(pos_buffer, &endptr, 10);
    if (errno != 0 || endptr == pos_buffer || *endptr != '\n' && *endptr != '\0')
    {
        fprintf(stderr, "Invalid input for positions\n");
        return EXIT_FAILURE;
    }

    if (temp_pos > SIZE_MAX)
    {
        fprintf(stderr, "Positions value too large\n");
        return EXIT_FAILURE;
    }

    positions = (size_t)temp_pos;

    result = left_rotate_string(buffer, positions, sizeof(buffer));
    if (result != 0)
    {
        fprintf(stderr, "Error rotating string\n");
        return EXIT_FAILURE;
    }

    printf("Rotated string: %s\n", buffer);

    return EXIT_SUCCESS;
}