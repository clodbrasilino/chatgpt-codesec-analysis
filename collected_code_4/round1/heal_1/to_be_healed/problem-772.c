/* Possible weaknesses found:
 *  stray '`' in program
 */
```
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* remove_words(char* str, int k) {
    #define MAX_SPACE 5000
    int n = strlen(str);
    char new_str[MAX_SPACE] = "";
    char *new_ptr = new_str;
    int word_len = 0;

    for (int i = 0; i <= n; i++) {
        if (str[i] == ' ' || str[i] == '\0') {
            if(word_len != k) {
                strncpy(new_ptr, str + i - word_len, word_len);
                new_ptr += word_len;
                *new_ptr = ' ';
                new_ptr++;
            }
            word_len = 0;
        } else {
            word_len++;
        }
    }
    
    if(strlen(new_str) > 0 && new_str[strlen(new_str)-1] == ' ')
        new_str[strlen(new_str)-1] = '\0';
    
    char* output = malloc(strlen(new_str)+1);
    strcpy(output, new_str);
    return output;
}

int main() {
    char str[] = "Remove all words of given length from this string";
    int k = 6;
    char* new_str = remove_words(str, k);
    printf("%s\n", new_str);
    free(new_str);
    return 0;
}