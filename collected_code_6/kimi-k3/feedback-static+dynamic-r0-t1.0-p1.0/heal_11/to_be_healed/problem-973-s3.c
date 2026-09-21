#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include <ctype.h>

#define BUFFER_SIZE 256
#define POS_BUFFER_SIZE 32

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
    if (len == buffer_size)
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char pos_buffer[POS_BUFFER_SIZE];
    size_t positions;
    unsigned long temp_pos;
    char *endptr;
    size_t len;
    int c;
    int valid_input;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer))
    {
        fprintf(stderr, "Input string too long\n");
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return EXIT_FAILURE;
    }

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

    len = strnlen(pos_buffer, sizeof(pos_buffer));
    if (len == sizeof(pos_buffer))
    {
        fprintf(stderr, "Positions input too long\n");
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return EXIT_FAILURE;
    }

    if (len > 0 && pos_buffer[len - 1] == '\n')
    {
        pos_buffer[len - 1] = '\0';
        len--;
    }

    valid_input = 1;
    if (len == 0)
    {
        valid_input = 0;
    }
    else
    {
        for (size_t i = 0; i < len; i++)
        {
            if (!isdigit((unsigned char)pos_buffer[i]))
            {
                valid_input = 0;
                break;
            }
        }
    }

    if (!valid_input)
    {
        fprintf(stderr, "Invalid input for positions\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    temp_pos = strtoul(pos_buffer, &endptr, 10);
    if (errno != 0 || endptr == pos_buffer || *endptr != '\0')
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