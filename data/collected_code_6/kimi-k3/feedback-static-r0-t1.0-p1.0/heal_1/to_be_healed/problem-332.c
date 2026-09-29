#include <stdio.h>
#include <string.h>
#include <limits.h>

#define CHARSET_SIZE (UCHAR_MAX + 1)

void countCharFrequency(const char *str, unsigned long frequency[])
{
    size_t i;
    if (str == NULL || frequency == NULL) {
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
    char input[1024];
    int i;
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    countCharFrequency(input, frequency);
    
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