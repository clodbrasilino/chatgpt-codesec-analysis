#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_IP_LENGTH 16
#define MAX_OCTET_LENGTH 4

static bool isValidOctet(const char *octet, size_t len)
{
    if (octet == NULL || len == 0 || len > 3) {
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        if (octet[i] < '0' || octet[i] > '9') {
            return false;
        }
    }

    if (len == 3) {
        int value = (octet[0] - '0') * 100 +
                    (octet[1] - '0') * 10 +
                    (octet[2] - '0');
        if (value > 255) {
            return false;
        }
    }

    return true;
}

static int removeLeadingZeros(const char *input, size_t inputLen,
                              char *output, size_t outputSize)
{
    if (input == NULL || output == NULL || outputSize < MAX_IP_LENGTH) {
        return -1;
    }

    if (inputLen == 0 || inputLen >= MAX_IP_LENGTH) {
        return -1;
    }

    size_t outIndex = 0;
    size_t i = 0;
    int octetCount = 0;

    while (i < inputLen && octetCount < 4) {
        size_t octetStart = i;

        while (i < inputLen && input[i] != '.') {
            i++;
        }

        size_t octetLen = i - octetStart;

        if (!isValidOctet(input + octetStart, octetLen)) {
            return -1;
        }

        size_t firstNonZero = octetStart;
        while (firstNonZero < i - 1 && input[firstNonZero] == '0') {
            firstNonZero++;
        }

        size_t digitsToCopy = i - firstNonZero;

        if (digitsToCopy > outputSize - outIndex - 1) {
            return -1;
        }

        memcpy(output + outIndex, input + firstNonZero, digitsToCopy);
        outIndex += digitsToCopy;

        if (i < inputLen && input[i] == '.') {
            if (octetCount < 3) {
                if (outIndex >= outputSize - 1) {
                    return -1;
                }
                output[outIndex++] = '.';
            }
            i++;
        }

        octetCount++;
    }

    if (octetCount != 4 || i != inputLen) {
        return -1;
    }

    if (outIndex >= outputSize) {
        return -1;
    }

    output[outIndex] = '\0';
    return 0;
}

int main(void)
{
    char output[MAX_IP_LENGTH] = {0};
    const char *testCases[] = {
        "192.168.001.001",
        "010.000.000.001",
        "255.255.255.255",
        "000.000.000.000",
        "001.002.003.004"
    };

    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numTests; i++) {
        memset(output, 0, sizeof(output));

        size_t inputLen = strnlen(testCases[i], MAX_IP_LENGTH);

        if (inputLen < MAX_IP_LENGTH &&
            removeLeadingZeros(testCases[i], inputLen,
                               output, sizeof(output)) == 0) {
            printf("Input:  %s\n", testCases[i]);
            printf("Output: %s\n\n", output);
        } else {
            printf("Input:  %s\n", testCases[i]);
            printf("Output: Invalid IP address\n\n");
        }
    }

    return 0;
}