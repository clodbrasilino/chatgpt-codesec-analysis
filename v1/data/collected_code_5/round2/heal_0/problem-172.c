#include <stdio.h>
#include <string.h>

int find_occurrence(const char* str, const char* sub)
{
    int count = 0;
    const char* temp = str;

    while((temp = strstr(temp, sub)) != NULL)
    {
        count++;
        temp++;
    }

    return count;
}

int main()
{
    const char* str = "1. list item 1. list item 1. list item 2. list item 2. list item 2. list item";
    const char* sub = "std";
   
    int res = find_occurrence(str, sub);

    printf("Number of occurrences of 'std' in the string is: %d\n", res);

    return 0;
}