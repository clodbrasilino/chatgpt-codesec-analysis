#include <stdio.h>
#include <string.h>
#include <limits.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)
#define INPUT_SIZE 1024

void countCharFrequency(const char *str, unsigned long frequency[], size_t freq_size)
{
    size_t i;
    if (str == NULL || frequency == NULL || freq_size < CHARSET_SIZE) {
        return;
    }
    for (i = 0; str[i] != '\0'; i++) {
        frequency[(unsigned char)str[i]]++;
    }
}

int main(void)
{
    unsigned long frequency[CHARSET_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    int i;
    int c;
    size_t len;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[sizeof(input) - 1] = '\0';
    
    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
    }
    
    countCharFrequency(input, frequency, CHARSET_SIZE);
    
    for (i = 0; i < CHARSET_SIZE; i++) {
        if (frequency[i] > 0) {
            if (i >= 32 && i <= 126) {
                printf("'%c': %lu\n", i, frequency[i]);
            } else {
                printf("0x%02x: %lu\n", i, frequency[i]);
            }
        }
    }
    
    return 0;
}