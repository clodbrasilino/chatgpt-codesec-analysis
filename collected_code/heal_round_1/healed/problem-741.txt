#include <stdbool.h>
#include <string.h>

bool isAllCharactersSame(const char str[])
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

int main() 
{
    char str[] = "aaaa";
    bool result = isAllCharactersSame(str);
    return 0;
}