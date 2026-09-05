#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_substring(const char *haystack, const char *needle, size_t *position)
{
    const char *result;
    
    if (haystack == NULL || needle == NULL || position == NULL)
    {
        return -1;
    }
    
    result = strstr(haystack, needle);
    
    if (result == NULL)
    {
        return 0;
    }
    
    *position = (size_t)(result - haystack);
    return 1;
}

int main(void)
{
    const char *text = "The quick brown fox jumps over the lazy dog";
    const char *pattern = "brown";
    size_t location = 0;
    int status;
    
    status = find_substring(text, pattern, &location);
    
    if (status == 1)
    {
        printf("Pattern found at index: %zu\n", location);
    }
    else if (status == 0)
    {
        printf("Pattern not found.\n");
    }
    else
    {
        fprintf(stderr, "Error: Invalid arguments provided.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}