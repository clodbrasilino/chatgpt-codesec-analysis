#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

#define BUFFER_SIZE 256

int left_rotate_string(char *str, size_t positions, size_t max_len)
{
    size_t len;
    size_t i;
    size_t j;
    char *temp;

    if (str == NULL || max_len == 0)
    {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == 0 || len == max_len)
    {
        return -1;
    }

    positions = positions % len;
    if (positions == 0)
    {
        return 0;
    }

    temp = (char *)malloc(positions);
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
    char buffer[BUFFER_SIZE];
    char *input;
    size_t positions;
    int result;
    char *endptr;
    unsigned long long temp_pos;
    size_t len;

    printf("Enter a string: ");
    input = fgets(buffer, sizeof(buffer), stdin);
    if (input == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer))
    {
        buffer[sizeof(buffer) - 1] = '\0';
        len = sizeof(buffer) - 1;
    }

    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0)
    {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    printf("Enter number of positions to rotate: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading positions\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp_pos = strtoull(buffer, &endptr, 10);
    
    if (errno != 0 || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input for positions\n");
        return EXIT_FAILURE;
    }

    if (temp_pos > SIZE_MAX)
    {
        fprintf(stderr, "Position value too large\n");
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