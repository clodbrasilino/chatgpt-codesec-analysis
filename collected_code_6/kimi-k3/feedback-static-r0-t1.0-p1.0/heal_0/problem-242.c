#include <stdio.h>
#include <string.h>
#include <stddef.h>

size_t count_characters(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }
    return strlen(str);
}

int main(void)
{
    char buffer[1024];
    
    printf("Enter a string: ");
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    printf("Total characters: %zu\n", count_characters(buffer));
    
    return 0;
}