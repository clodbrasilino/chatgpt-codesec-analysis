#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MAX_CHARS 256

bool areAllCharsUnique(char *str)
{
    bool chars[MAX_CHARS] = {false};

    for (int i = 0; str[i]; i++)
    {
        int index = (int)str[i];
        if (chars[index] == true)
        {
            return false;
        }
        chars[index] = true;
    }
    return true;
}

int main()
{
    char str[] = "Hello, World!";
    if (areAllCharsUnique(str))
    {
        printf("The String has all unique characters\n");
    }
    else
    {
        printf("The String does not have all unique characters\n");
    }
    return 0;
}