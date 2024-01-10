#include <stdio.h>
#include <string.h>
#include <ctype.h>

_Bool containsNullTermination(const char* s, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (s[i] == '\0')
            return 1;
    }
    return 0;
}

void snakeToCamel(char* s, size_t len)
{
    size_t j;
    for (size_t i = 0; i < len; i++) {
        if (s[i] == '_') {
            for (j = i; j < len - 1; j++) {
                s[j] = s[j+1];
            }
            s[len - 1] = '\0';
            len--;
            if(islower(s[i])) {
                s[i] = toupper(s[i]);
            }
        }
    }
}

int main()
{
    char str[] = "convert_snake_case_to_camel_case";
    size_t len = sizeof str / sizeof str[0];
    
    if (!containsNullTermination(str, len))
    {
        printf("The string is not null terminated.\n");
        return 1;
    }
    
    snakeToCamel(str, len);
    
    printf("%s\n", str);
    
    return 0;
}
