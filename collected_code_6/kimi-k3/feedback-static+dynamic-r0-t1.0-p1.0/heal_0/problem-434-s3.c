#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str)
{
    if (str == NULL)
        return false;
    
    size_t len = strlen(str);
    
    if (len < 2)
        return false;
    
    if (str[0] != 'a')
        return false;
    
    for (size_t i = 1; i < len; i++)
    {
        if (str[i] != 'b')
            return false;
    }
    
    return true;
}

int main(void)
{
    const char *test1 = "ab";
    const char *test2 = "abb";
    const char *test3 = "abbb";
    const char *test4 = "a";
    const char *test5 = "b";
    const char *test6 = "abc";
    const char *test7 = "ba";
    
    printf("'%s': %s\n", test1, match_pattern(test1) ? "Match" : "No match");
    printf("'%s': %s\n", test2, match_pattern(test2) ? "Match" : "No match");
    printf("'%s': %s\n", test3, match_pattern(test3) ? "Match" : "No match");
    printf("'%s': %s\n", test4, match_pattern(test4) ? "Match" : "No match");
    printf("'%s': %s\n", test5, match_pattern(test5) ? "Match" : "No match");
    printf("'%s': %s\n", test6, match_pattern(test6) ? "Match" : "No match");
    printf("'%s': %s\n", test7, match_pattern(test7) ? "Match" : "No match");
    
    return 0;
}