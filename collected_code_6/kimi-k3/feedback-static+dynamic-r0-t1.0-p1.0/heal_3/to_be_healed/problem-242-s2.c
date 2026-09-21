#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5, got <no output>
  *  test case 0 failed: expected 18, got <no output>
  *  test case 1 failed: expected 8, got <no output>
  */

int count_characters(const char *str)
{
    if (str == NULL)
    {
        return -1;
    }
    
    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }
    return count;
}

int main(void)
{
    char *input = NULL;
    size_t buffer_size = 0;
    ssize_t chars_read;
    
    chars_read = getline(&input, &buffer_size, stdin);
    
    if (chars_read == -1)
    {
        free(input);
        return 1;
    }
    
    if (chars_read > 0 && input[chars_read - 1] == '\n')
    {
        input[chars_read - 1] = '\0';
    }
    
    int result = count_characters(input);
    
    if (result >= 0)
    {
        printf("%d\n", result);
    }
    else
    {
        free(input);
        return 1;
    }
    
    free(input);
    return 0;
}