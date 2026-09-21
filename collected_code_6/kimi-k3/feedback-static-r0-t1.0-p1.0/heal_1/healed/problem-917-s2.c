#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

void find_sequences(const char *str, size_t max_len)
{
    if (str == NULL || max_len == 0)
    {
        return;
    }

    size_t len = strnlen(str, max_len);
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
                size_t seq_len = j - start;
                if (seq_len <= INT_MAX)
                {
                    printf("Found sequence: %.*s\n", (int)seq_len, str + start);
                }
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
    size_t max_len = 1024;
    
    printf("Input string: %s\n", test_string);
    printf("Sequences found:\n");
    
    find_sequences(test_string, max_len);
    
    return 0;
}