#include <stdbool.h>

bool isAllCharactersSame(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != str[0])
        {
            return false;
        }
        i++;
    }
    return true;
}