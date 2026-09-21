#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

bool canRearrange(const char *str, size_t len)
{
    int freq[UCHAR_MAX + 1] = {0};
    size_t i;
    int maxFreq = 0;

    if (str == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    for (i = 0; i <= UCHAR_MAX; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }

    return maxFreq <= (int)((len + 1) / 2);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    /* Possible weaknesses found:
     *  The scope of the variable 'len' can be reduced. [variableScope]
     */
    size_t len;

    if (fgets(input, sizeof(input), stdin) != NULL) {
        len = strcspn(input, "\n");
        input[len] = '\0';

        if (canRearrange(input, len)) {
            printf("true\n");
        } else {
            printf("false\n");
        }
    }

    return 0;
}