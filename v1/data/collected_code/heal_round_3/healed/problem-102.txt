#include <stdio.h>
#include <string.h>
#include <ctype.h>

void snakeToCamel(char* s)
{
    if(!s)return; // nullptr check
    size_t len = strlen(s);
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
    
    snakeToCamel(str);
    
    printf("%s\n", str);
    
    return 0;
}