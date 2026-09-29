#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP_MAX_LEN 15
#define RESULT_SIZE 16

_Static_assert(RESULT_SIZE > IP_MAX_LEN,
               "result buffer must hold the longest normalized IPv4 string plus its terminator");

static size_t bounded_strnlen(const char *s, size_t max_len)
{
    size_t n = 0;

    if (s == NULL)
    {
        return 0;
    }

    while (n < max_len && s[n] != '\0')
    {
        n++;
    }

    return n;
}

int remove_leading_zeros(const char *ip, char *result, size_t result_size)
{
    size_t len;
    size_t i = 0;
    size_t j = 0;
    int segment = 0;

    if (ip == NULL || result == NULL || result_size == 0)
    {
        return -1;
    }

    len = bounded_strnlen(ip, (size_t)IP_MAX_LEN + 1);
    if (len == 0 || len > IP_MAX_LEN)
    {
        return -1;
    }

    while (i <= len)
    {
        size_t octet_start = i;
        size_t octet_len;
        size_t m;

        while (i < len && ip[i] != '.')
        {
            if (ip[i] < '0' || ip[i] > '9')
            {
                return -1;
            }
            i++;
        }

        octet_len = i - octet_start;

        if (octet_len == 0 || octet_len > 3)
        {
            return -1;
        }

        if (octet_len == 3)
        {
            int value = (ip[octet_start] - '0') * 100 +
                        (ip[octet_start + 1] - '0') * 10 +
                        (ip[octet_start + 2] - '0');
            if (value > 255)
            {
                return -1;
            }
        }

        while (octet_len > 1 && ip[octet_start] == '0')
        {
            octet_start++;
            octet_len--;
        }

        if (octet_len >= result_size || j >= result_size - octet_len - 1)
        {
            return -1;
        }

        for (m = 0; m < octet_len; m++)
        {
            result[j + m] = ip[octet_start + m];
        }
        j += octet_len;

        if (i < len && ip[i] == '.')
        {
            if (segment == 3)
            {
                return -1;
            }
            if (j + 1 >= result_size)
            {
                return -1;
            }
            result[j++] = '.';
            i++;
            segment++;
        }
        else
        {
            break;
        }
    }

    if (segment != 3 || i != len)
    {
        return -1;
    }

    result[j] = '\0';
    return 0;
}

int main(void)
{
    const char *test_ips[] = {
        "192.168.001.001",
        "010.000.000.001",
        "001.002.003.004",
        "255.255.255.255",
        "0.0.0.0",
        "000.000.000.000"
    };
    const size_t num_tests = sizeof(test_ips) / sizeof(test_ips[0]);
    char *result = NULL;
    size_t k;

    result = calloc((size_t)RESULT_SIZE, sizeof(char));
    if (result == NULL)
    {
        fprintf(stderr, "Failed to allocate result buffer\n");
        return EXIT_FAILURE;
    }

    for (k = 0; k < num_tests; k++)
    {
        memset(result, 0, (size_t)RESULT_SIZE);

        if (remove_leading_zeros(test_ips[k], result, (size_t)RESULT_SIZE) == 0)
        {
            printf("Input:  %s\n", test_ips[k]);
            printf("Output: %s\n\n", result);
        }
        else
        {
            printf("Invalid IP address: %s\n\n", test_ips[k]);
        }
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}