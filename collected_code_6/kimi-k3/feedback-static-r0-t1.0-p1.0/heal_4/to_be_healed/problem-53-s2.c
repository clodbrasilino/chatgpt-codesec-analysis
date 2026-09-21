#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool check_first_last_equal(const char *str, size_t max_len)
{
    size_t len = 0;
    
    if (str == NULL || max_len == 0)
    {
        return false;
    }
    
    while (len < max_len && str[len] != '\0')
    {
        len++;
    }
    
    if (len == 0)
    {
        return false;
    }
    
    return str[0] == str[len - 1];
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    
    printf("Enter a string: ");
    
    read_len = getline(&buffer, &buffer_size, stdin);
    
    if (read_len == -1)
    {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }
    
    if (read_len > 0 && buffer[read_len - 1] == '\n')
    {
        buffer[read_len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'read_len' is assigned a value that is never used. [unreadVariable]
         */
        read_len--;
    }
    
    if (check_first_last_equal(buffer, buffer_size))
    {
        printf("First and last characters are equal\n");
    }
    else
    {
        printf("First and last characters are not equal\n");
    }
    
    free(buffer);
    return 0;
}