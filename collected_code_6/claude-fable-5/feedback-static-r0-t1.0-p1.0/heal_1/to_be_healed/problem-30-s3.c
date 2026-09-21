#include <stdio.h>
#include <string.h>

unsigned long count_substrings(const char *str)
{
    unsigned long freq[256] = {0};
    unsigned long total = 0;
    size_t i;
    size_t len;

    if (str == NULL)
    {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    for (i = 0; i < len; i++)
    {
        freq[(unsigned char)str[i]]++;
    }

    for (i = 0; i < 256; i++)
    {
        total += (freq[i] * (freq[i] + 1)) / 2;
    }

    return total;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    unsigned long result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }

    result = count_substrings(buffer);

    if (printf("%lu\n", result) < 0)
    {
        return 1;
    }

    return 0;
}