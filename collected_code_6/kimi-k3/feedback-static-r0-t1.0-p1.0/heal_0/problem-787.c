#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_abbb(const char *str)
{
    if (str == NULL)
    {
        return false;
    }
    
    if (strcmp(str, "abbb") == 0)
    {
        return true;
    }
    
    return false;
}

int main(void)
{
    const char *test1 = "abbb";
    const char *test2 = "ab";
    const char *test3 = "abbbb";
    const char *test4 = "bbb";
    
    printf("Test 1: %s -> %s\n", test1, match_abbb(test1) ? "Match" : "No match");
    printf("Test 2: %s -> %s\n", test2, match_abbb(test2) ? "Match" : "No match");
    printf("Test 3: %s -> %s\n", test3, match_abbb(test3) ? "Match" : "No match");
    printf("Test 4: %s -> %s\n", test4, match_abbb(test4) ? "Match" : "No match");
    
    return 0;
}