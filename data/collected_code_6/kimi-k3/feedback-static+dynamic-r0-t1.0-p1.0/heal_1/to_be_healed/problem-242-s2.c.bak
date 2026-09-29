#include <stdio.h>
#include <string.h>
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
    char input[256];
    
    printf("Enter a string: ");
    
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    input[strcspn(input, "\n")] = '\0';
    
    int result = count_characters(input);
    
    if (result >= 0)
    {
        printf("Total characters: %d\n", result);
    }
    else
    {
        fprintf(stderr, "Error counting characters\n");
        return 1;
    }
    
    return 0;
}