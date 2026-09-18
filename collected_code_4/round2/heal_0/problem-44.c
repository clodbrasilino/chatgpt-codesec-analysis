#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool match_word_beginning(const char* str, const char* word) 
{
    if (str == NULL || word == NULL) 
    {
        return false;
    }
    if (strncmp(str, word, strlen(word)) == 0) 
    {
        return true;
    }
    return false;
}

int main() 
{
    const char* str = "Hello world";
    const char* word_to_match = "Hello";

    if (match_word_beginning(str, word_to_match)) 
    {
       printf("The word matches at the beginning of the string.\n");
    } 
    else 
    {
       printf("The word doesn't match at the beginning of the string.\n");
    }

  return 0;
}