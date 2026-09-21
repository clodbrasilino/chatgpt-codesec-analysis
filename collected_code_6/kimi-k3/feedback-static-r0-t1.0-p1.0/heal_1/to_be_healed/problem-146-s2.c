#include <stdio.h>
#include <string.h>
#include <limits.h>

int sum_ascii_values(const char *str, int *result)
{
    int sum;
    size_t i;
    size_t len;

    if (str == NULL || result == NULL)
    {
        return -1;
    }

    sum = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len; i++)
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
    char buffer[256];
    int total;
    int status;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    status = sum_ascii_values(buffer, &total);

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