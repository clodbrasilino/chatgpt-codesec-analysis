#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ab[3];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char ba[3];
    char ca = *(const char *)a;
    char cb = *(const char *)b;

    ab[0] = ca;
    ab[1] = cb;
    ab[2] = '\0';

    ba[0] = cb;
    ba[1] = ca;
    ba[2] = '\0';

    return strcmp(ba, ab);
}

void findLargestNumber(char digits[], size_t n)
{
    if (n == 0)
    {
        return;
    }
    qsort(digits, n, sizeof(char), compare);
}

int main(void)
{
    char digits[] = {'5', '4', '6', '8', '0'};
    size_t n = sizeof(digits) / sizeof(digits[0]);
    size_t i;

    findLargestNumber(digits, n);

    printf("Largest number: ");
    for (i = 0; i < n; i++)
    {
        putchar(digits[i]);
    }
    putchar('\n');

    return 0;
}