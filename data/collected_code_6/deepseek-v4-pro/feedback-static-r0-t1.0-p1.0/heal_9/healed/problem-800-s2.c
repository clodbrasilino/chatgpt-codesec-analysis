#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

char *remove_whitespaces(char *str)
{
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    const char *read = str;
    size_t read_index = 0;
    char *write = str;
    size_t write_index = 0;
    
    while (read_index < len && *read != '\0') {
        if (!isspace((unsigned char)*read)) {
            if (write_index < len) {
                *write++ = *read;
                write_index++;
            }
        }
        read++;
        read_index++;
    }
    
    if (write_index < len) {
        *write = '\0';
    } else if (len > 0) {
        str[len - 1] = '\0';
    }
    
    return str;
}

int main(void)
{
    char str1[] = "Hello World from C";
    char str2[] = "  leading and trailing  ";
    char str3[] = "\tTab\nNewline\rCarriage";
    char str4[] = "NoWhitespaces";
    char str5[] = "";
    
    printf("Original: '%s'\n", str1);
    remove_whitespaces(str1);
    printf("Modified: '%s'\n\n", str1);
    
    printf("Original: '%s'\n", str2);
    remove_whitespaces(str2);
    printf("Modified: '%s'\n\n", str2);
    
    printf("Original: '\\tTab\\nNewline\\rCarriage'\n");
    remove_whitespaces(str3);
    printf("Modified: '%s'\n\n", str3);
    
    printf("Original: '%s'\n", str4);
    remove_whitespaces(str4);
    printf("Modified: '%s'\n\n", str4);
    
    printf("Original: '%s'\n", str5);
    remove_whitespaces(str5);
    printf("Modified: '%s'\n", str5);
    
    return 0;
}