#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void find_sequences(const char *str)
{
    if (str == NULL)
    {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;

    while (i < len)
    {
        if (isupper((unsigned char)str[i]))
        {
            size_t start = i;
            size_t j = i + 1;

            while (j < len && islower((unsigned char)str[j]))
            {
                j++;
            }

            if (j > start + 1)
            {
                printf("Found sequence: %.*s\n", (int)(j - start), str + start);
            }

            i = j;
        }
        else
        {
            i++;
        }
    }
}

int main(void)
{
    const char *test_string = "Hello World This Is A Test String With ABCDef And XyZ";
    
    printf("Input string: %s\n", test_string);
    printf("Sequences found:\n");
    
    find_sequences(test_string);
    
    return 0;
}