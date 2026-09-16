#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** split_at_uppercase(const char* str, int* out_count) {
    if (str == NULL || out_count == NULL) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    int len = strlen(str);
    int count = 0;
    
    for (int i = 0; i < len; i++) {
        if (isupper((unsigned char)str[i]) || i == 0) {
            count++;
        }
    }

    char** result = (char**)malloc(count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    int current_word = 0;
    int start = 0;

    for (int i = 1; i <= len; i++) {
        if (isupper((unsigned char)str[i]) || i == len) {
            int word_len = i - start;
            result[current_word] = (char*)malloc((word_len + 1) * sizeof(char));
            
            if (result[current_word] == NULL) {
                for (int j = 0; j < current_word; j++) {
                    free(result[j]);
                }
                free(result);
                *out_count = 0;
                return NULL;
            }
            
            strncpy(result[current_word], str + start, word_len);
            result[current_word][word_len] = '\0';
            
            start = i;
            current_word++;
        }
    }

    *out_count = count;
    return result;
}

int main(void) {
    const char* test_str = "SplitThisStringAtUppercaseLetters";
    int count = 0;
    
    char** words = split_at_uppercase(test_str, &count);
    
    if (words != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", words[i]);
            free(words[i]);
        }
        free(words);
    }
    
    return 0;
}