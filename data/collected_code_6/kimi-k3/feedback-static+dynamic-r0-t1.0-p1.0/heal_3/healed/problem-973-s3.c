#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

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
    char buffer[256];
    char pos_buffer[32];
    size_t positions;
    unsigned long temp_pos;
    char *endptr;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    printf("Enter number of positions to rotate: ");
    if (fgets(pos_buffer, sizeof(pos_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading positions\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp_pos = strtoul(pos_buffer, &endptr, 10);
    if (errno != 0 || endptr == pos_buffer || (*endptr != '\n' && *endptr != '\0'))
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

    if (left_rotate_string(buffer, positions, sizeof(buffer)) != 0)
    {
        fprintf(stderr, "Error rotating string\n");
        return EXIT_FAILURE;
    }

    printf("Rotated string: %s\n", buffer);

    return EXIT_SUCCESS;
}