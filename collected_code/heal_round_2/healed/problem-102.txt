#include <stdio.h>
#include <string.h>

void snakeToCamel(char* s)
{
    int len = strlen(s);
    int i, j;

    for (i = 0; i < len; i++) {
        if (s[i] == '_') {
            for (j = i; j < len - 1; j++) {
                s[j] = s[j+1];
            }
            s[len - 1] = '\0';
            len--;
            if(s[i] >= 'a' && s[i] <= 'z') {
                s[i] = s[i] - 32;
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
