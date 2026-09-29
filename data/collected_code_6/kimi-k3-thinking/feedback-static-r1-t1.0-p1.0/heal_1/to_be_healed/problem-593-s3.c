#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IP_MAX_LEN 15
#define RESULT_SIZE 16

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(ip);
    if (len == 0 || len > IP_MAX_LEN)
    {
        return -1;
    }

    while (i <= len)
    {
        size_t octet_start = i;
        size_t octet_len;

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

        if (j + octet_len + 1 >= result_size)
        {
            return -1;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + j, ip + octet_start, octet_len);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[RESULT_SIZE];
    size_t k;

    for (k = 0; k < num_tests; k++)
    {
        if (remove_leading_zeros(test_ips[k], result, sizeof(result)) == 0)
        {
            printf("Input:  %s\n", test_ips[k]);
            printf("Output: %s\n\n", result);
        }
        else
        {
            printf("Invalid IP address: %s\n\n", test_ips[k]);
        }
    }

    return EXIT_SUCCESS;
}