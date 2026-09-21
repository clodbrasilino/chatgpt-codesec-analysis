#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int sum_ascii_values(const char *str, size_t len, int *result)
{
    int sum;
    size_t i;

    if (str == NULL || result == NULL)
    {
        return -1;
    }

    sum = 0;

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
    char buffer[256];
    size_t len;
    int total;
    int status;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin))
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        fprintf(stderr, "Error: Input too long\n");
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