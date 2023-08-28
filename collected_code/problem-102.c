#include <string.h>

void snakeToCamel(char* s)
{
    int len = strlen(s);
    int i, j;
    
    for (i = 0; i < len-1; i++) {
        if (s[i] == '_') {
            for (j = i; j < len-1; j++) {
                s[j] = s[j+1];
            }
            len--;
            s[i] = s[i] & ~('a' - 'A'); // Convert lowercase to uppercase
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