#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int minimumNoOfSwaps(char str[])
{
    int len = strlen(str);
    int leftBracket = 0, rightBracket = 0;
    int swap = 0 , imbalance = 0;
  
    for (int i =0; i< len; i++)
    {
        if(str[i] == '[')
        {
            leftBracket++;
            if(imbalance > 0)
            {
                swap += imbalance;
                imbalance--;    
            }
        }
        else if(str[i] == ']')
        {
            rightBracket++;
            imbalance = (rightBracket-leftBracket);
        }
    }

    if (leftBracket != rightBracket)
        return -1;
        
    return swap;
}

int main()
{
    char str[] = "][][";   
    int res = minimumNoOfSwaps(str);

    if (res != -1)
        printf("Minimum number of swaps for balanced brackets is %d", res);
    else
        printf("The brackets cannot be balanced");

    return 0;
}