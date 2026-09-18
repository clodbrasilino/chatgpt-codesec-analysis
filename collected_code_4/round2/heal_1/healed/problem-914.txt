#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isAlternating(char* str)
{
    int len = strlen(str);
    if (len < 2) 
    {
        return false;
    }
    
    char first = str[0];
    char second = str[1];

    for (int i = 2; i < len; i++) 
    {
        if (i % 2 == 0) 
        {
            if (str[i] != first) 
            {
                return false;
            }
        }
        else
        {
            if (str[i] != second) 
            {
                return false;
            }
        }
    }

    return true;
}

int main() 
{
    char *str = "ABABABAB";
    
    if(isAlternating(str))
    {
        printf("Yes, the string is made up of two alternating characters\n");
    }
    else
    {
        printf("No, the string is not made up of two alternating characters\n");
    }

    return 0;
}