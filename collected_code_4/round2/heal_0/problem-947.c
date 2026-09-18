#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int find_shortest_word_length(const char *str)
{
    int min_length = strlen(str);
    char *dupstr = strdup(str);
    char *token = strtok(dupstr, " ");

    while (token != NULL) {
        int word_length = strlen(token);
        if (word_length < min_length) {
            min_length = word_length;
        }
        token = strtok(NULL, " ");
    }

    free(dupstr);
    return min_length;
}


int main() 
{
    char str[100];
    printf("Enter a sentence: \n");
    fgets(str, 100, stdin);
    str[strlen(str)-1] = '\0';
    
    int length = find_shortest_word_length(str);
    printf("Length of shortest word is %d\n", length);
    
    return 0;
}