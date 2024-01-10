#include <stdio.h>
#include <string.h>

int romanToInt(const char *s)
{
    int result = 0;
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(s);

    for (int i = 0; i < length; i++) 
    {
        switch(s[i]) 
        {
            case 'I':
                if (i + 1 < length && (s[i + 1] == 'V' || s[i + 1] == 'X')) 
                {
                    result -= 1;
                } 
                else 
                {
                    result += 1;
                }
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                if (i + 1 < length && (s[i + 1] == 'L' || s[i + 1] == 'C')) 
                {
                    result -= 10;
                } 
                else 
                {
                    result += 10;
                }
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                if (i + 1 < length && (s[i + 1] == 'D' || s[i + 1] == 'M')) 
                {
                    result -= 100;
                } 
                else 
                {
                    result += 100;
                }
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;
        }
    }
    return result;
}

int main() 
{
    char roman_numeral[] = "MCMIV";
    printf("%d\n", romanToInt(roman_numeral));
    return 0;
}