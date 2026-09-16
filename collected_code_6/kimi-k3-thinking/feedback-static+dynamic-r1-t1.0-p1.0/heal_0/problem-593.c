#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 64

char *removeLeadingZeros(const char *ip, char *result, size_t resultSize)
{
    size_t i;
    size_t j = 0;
    size_t ipLen;
    int segmentStart = 1;

    if (ip == NULL || result == NULL || resultSize == 0) {
        return NULL;
    }

    ipLen = strlen(ip);
    if (ipLen == 0 || ipLen >= resultSize) {
        return NULL;
    }

    for (i = 0; i < ipLen; i++) {
        if (!isdigit((unsigned char)ip[i]) && ip[i] != '.') {
            return NULL;
        }
    }

    i = 0;
    while (i < ipLen) {
        if (ip[i] == '.') {
            result[j++] = ip[i++];
            segmentStart = 1;
        } else if (segmentStart && ip[i] == '0' && i + 1 < ipLen && ip[i + 1] != '.') {
            i++;
        } else {
            segmentStart = 0;
            result[j++] = ip[i++];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *testIps[] = {
        "192.168.001.010",
        "010.010.010.010",
        "0.0.0.0",
        "255.255.255.255",
        "001.002.003.004",
        "100.000.001.0"
    };
    char result[BUFFER_SIZE];
    size_t numTests = sizeof(testIps) / sizeof(testIps[0]);
    size_t k;

    for (k = 0; k < numTests; k++) {
        if (removeLeadingZeros(testIps[k], result, sizeof(result)) != NULL) {
            printf("Original: %-18s Cleaned: %s\n", testIps[k], result);
        } else {
            fprintf(stderr, "Error processing: %s\n", testIps[k]);
        }
    }

    return 0;
}