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
    int result;
    
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    
    ab[0] = *(const char *)a;
    ab[1] = *(const char *)b;
    ab[2] = '\0';
    
    ba[0] = *(const char *)b;
    ba[1] = *(const char *)a;
    ba[2] = '\0';
    
    result = strncmp(ba, ab, sizeof(ab));
    
    return result;
}

void findLargestNumber(char digits[], int n)
{
    if (digits == NULL || n <= 0)
    {
        return;
    }
    
    qsort(digits, (size_t)n, sizeof(char), compare);
}

int main(void)
{
    char digits[] = {'5', '4', '6', '8', '0'};
    int n = (int)(sizeof(digits) / sizeof(digits[0]));
    int i;

    findLargestNumber(digits, n);

    printf("Largest number: ");
    for (i = 0; i < n; i++)
    {
        putchar(digits[i]);
    }
    putchar('\n');

    return 0;
}