#include <stdio.h>
#include <string.h>

int length_of_last_word(char* str)
{
    if(str == NULL) {
        return 0;
    }
    
    int len = strlen(str);
    int count = 0;
    
    for(int i=len-1; i>=0; i--) {
        if(str[i] == ' ') {
            if(count == 0) {
                continue;
            } else {
                break;
            }
        } else {
            count++;
        }
    }
    
    return count;
}

int main()
{
    char str[] = "I am an experienced C developer";
    printf("Length of last word: %d\n", length_of_last_word(str));
    
    return 0;
}