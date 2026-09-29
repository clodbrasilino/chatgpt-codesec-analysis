#include <stdio.h>

unsigned long count_hexadecimal_numbers(unsigned long start, unsigned long end)
{
    unsigned long count = 0;
    for(unsigned long i = start; i <= end; ++i) {
        ++count;
    }
    return count;
}

int main()
{
    unsigned long start, end;
    printf("Enter range start: ");
    scanf("%lu", &start);
    
    printf("Enter range end: ");
    scanf("%lu", &end);
    
    if(start > end) {
        printf("Start of range is greater than the end. Exiting.\n");
        return -1;
    }
    
    unsigned long count = count_hexadecimal_numbers(start, end);
    
    printf("Count of hexadecimal numbers between %lu and %lu is: %lu\n", start, end, count);

    return 0;
}