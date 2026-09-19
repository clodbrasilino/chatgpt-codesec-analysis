#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *removeLeadingZeroes(const char *ipAddress)
{
    size_t length;
    size_t i;
    size_t j;
    char *result;

    if (ipAddress == NULL)
    {
        return NULL;
    }

    length = strlen(ipAddress);
    if (length == 0)
    {
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL)
    {
        return NULL;
    }

    i = 0;
    j = 0;

    while (i < length)
    {
        size_t start = i;

        while (i < length && ipAddress[i] == '0')
        {
            i++;
        }

        if (i >= length || ipAddress[i] == '.')
        {
            if (i == start)
            {
                free(result);
                return NULL;
            }
            result[j++] = '0';
        }
        else
        {
            while (i < length && ipAddress[i] != '.')
            {
                if (ipAddress[i] < '0' || ipAddress[i] > '9')
                {
                    free(result);
                    return NULL;
                }
                result[j++] = ipAddress[i++];
            }
        }

        if (i < length && ipAddress[i] == '.')
        {
            result[j++] = ipAddress[i++];
            if (i >= length)
            {
                free(result);
                return NULL;
            }
        }
    }

    result[j] = '\0';
    return result;
}

int main(void)
{
    const char *testCases[] = {
        "192.168.001.001",
        "010.000.000.001",
        "000.000.000.000",
        "255.255.255.255",
        "001.002.003.004"
    };
    size_t count = sizeof(testCases) / sizeof(testCases[0]);
    size_t index;

    for (index = 0; index < count; index++)
    {
        char *cleaned = removeLeadingZeroes(testCases[index]);

        if (cleaned == NULL)
        {
            fprintf(stderr, "Failed to process: %s\n", testCases[index]);
        }
        else
        {
            printf("Original: %-18s Cleaned: %s\n", testCases[index], cleaned);
            free(cleaned);
        }
    }

    return 0;
}