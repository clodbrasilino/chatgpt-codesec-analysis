#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define BUFFER_SIZE 256

int sum_ascii_values(const char *str, size_t str_len, int *result)
{
    int sum;
    size_t i;

    if (str == NULL || result == NULL)
    {
        return -1;
    }

    sum = 0;

    for (i = 0; i < str_len; i++)
    {
        if (sum > INT_MAX - (unsigned char)str[i])
        {
            return -2;
        }
        sum += (unsigned char)str[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    int total;
    int status;
    size_t len;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strcspn(buffer, "\n");
    buffer[len] = '\0';

    status = sum_ascii_values(buffer, len, &total);

    if (status == 0)
    {
        printf("Total ASCII value: %d\n", total);
    }
    else if (status == -2)
    {
        fprintf(stderr, "Error: Integer overflow occurred\n");
        return 1;
    }
    else
    {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    return 0;
}