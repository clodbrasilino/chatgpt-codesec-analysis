#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    char ab[3];
    char ba[3];
    int result;
    
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    
    if (snprintf(ab, sizeof(ab), "%c%c", *(const char *)a, *(const char *)b) < 0)
    {
        return 0;
    }
    
    if (snprintf(ba, sizeof(ba), "%c%c", *(const char *)b, *(const char *)a) < 0)
    {
        return 0;
    }
    
    result = strcmp(ba, ab);
    
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