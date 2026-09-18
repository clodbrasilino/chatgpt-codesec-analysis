#include <stdio.h>
#include <string.h>

int value(char r) 
{ 
    if (r == 'I') 
        return 1; 
    if (r == 'V') 
        return 5; 
    if (r == 'X') 
        return 10; 
    if (r == 'L') 
        return 50; 
    if (r == 'C') 
        return 100; 
    if (r == 'D') 
        return 500; 
    if (r == 'M') 
        return 1000; 
  
    return -1; 
} 

int romanToDecimal(char *str) 
{ 
    int result = 0;
    int strLength = strlen(str);

    for (int i=0; i<strLength; i++) 
    { 
        int s1 = value(str[i]); 

        if (i+1 < strLength) 
        { 
            int s2 = value(str[i+1]); 

            if (s1 >= s2) 
            {
                result = result + s1; 
            }
            else
            { 
                result = result + s2 - s1; 
                i++; 
            } 
        } 
        else
        {
            result = result + s1;
            i++; 
        } 
    } 
    return result; 
} 
  
int main() 
{ 
    char romanNumeral[16];
    printf("Enter a Roman Numeral: ");
    scanf("%s", romanNumeral);

    int decimal = romanToDecimal(romanNumeral);

    if(decimal != -1)
    {
        printf("The equivalent of the Roman numeral in decimal is : %d\n", romanToDecimal(romanNumeral)); 
    } 
    else 
    { 
        printf("%s is not a valid Roman numeral.", romanNumeral);
    }

    return 0; 
} 