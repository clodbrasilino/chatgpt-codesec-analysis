#include <stdio.h>
#include <string.h>

#define SIZE 256

int canRearrange(char* str)
{
    int char_count[SIZE] = {0};
    int i, len;

    len = strlen(str);

    for (i = 0; i < len; i++) 
        char_count[str[i]]++;

    for (i = 0; i < len; i++)
    {
        if(char_count[str[i]] > (len + 1) / 2)
            return 0;
    }

    return 1;
}

int main()
{
    char str[] = "aab";

    if (canRearrange(str) == 1)
        printf("Can be rearranged\n");
    else
        printf("Cannot be rearranged\n");

    return 0;
}