#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMaxDifference(const char *str, size_t len)
{
    int currentSum;
    int maxSum;
    size_t i;

    if (str == NULL || len == 0U) {
        return -1;
    }

    currentSum = 0;
    maxSum = -1;

    for (i = 0U; i < len; i++) {
        if (str[i] == '0') {
            currentSum += 1;
        } else if (str[i] == '1') {
            currentSum -= 1;
        } else {
            return -1;
        }

        if (currentSum < 0) {
            currentSum = 0;
        }

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    return maxSum;
}

int main(void)
{
    const char *testStrings[] = {
        "11000010001",
        "1111",
        "0000",
        "101010"
    };
    size_t numTests;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    int result;

    numTests = sizeof(testStrings) / sizeof(testStrings[0]);

    for (i = 0U; i < numTests; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        result = findMaxDifference(testStrings[i], strlen(testStrings[i]));
        if (result < 0) {
            if (printf("String: %s -> No valid substring with more 0s than 1s\n",
                       testStrings[i]) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("String: %s -> Maximum difference: %d\n",
                       testStrings[i], result) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}