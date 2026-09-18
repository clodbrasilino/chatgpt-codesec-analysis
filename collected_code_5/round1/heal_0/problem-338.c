#include <stdio.h>
#include <string.h>

int countSubstring(char str[])
{
    int length = strlen(str);
    int result = 0;
    int start;
    int end;

    for(start = 0; start < length; start++)
    {
        for(end = start; end < length; end++)
        {
            if(str[start] == str[end])
            {
                result++;
            }
        }
    }

    return result;
}

int main()
{
    char str[] = "abcab";
    printf("Number of substrings with same first and last characters is: %d", countSubstring(str));
    return 0;
}