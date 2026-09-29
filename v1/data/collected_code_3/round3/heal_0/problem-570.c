#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

void removeWords(char *str, const char *toRemove)
{
    int i, j, stringLen, toRemoveLen;
    int found;

    stringLen   = strlen(str);      
    toRemoveLen = strlen(toRemove); 

    for(i=0; i <= stringLen - toRemoveLen; i++)
    {
        found = 1;
        for(j=0; j < toRemoveLen; j++)
        {
            if(str[i + j] != toRemove[j])
            {
                found = 0;
                break;
            }
        }

        if(str[i + j] == ' ' || str[i + j] == '\t' || str[i + j] == '\n' || str[i + j] == '\0')
        {
            found = 1;
        }

        if(found == 1)
        {
            for(j=i; j <= stringLen - toRemoveLen; j++)
            {
                str[j] = str[j + toRemoveLen];
            }

            stringLen = stringLen - toRemoveLen;

            i--;
        }
    }
}

int main()
{
    char str[MAX_SIZE];
    char toRemove[MAX_SIZE];

    printf("Enter any string: ");
    fgets(str, MAX_SIZE, stdin);

    printf("Enter word to remove: ");
    fgets(toRemove, MAX_SIZE, stdin);

    str[strlen(str) - 1] = '\0';
    toRemove[strlen(toRemove) - 1] = '\0';

    removeWords(str, toRemove);

    printf("String after removing '%s': \n%s", toRemove, str);

    return 0;
}