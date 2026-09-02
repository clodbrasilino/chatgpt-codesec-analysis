#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 256

char **find_words(const char *str, int *count) {
    regex_t regex;
    regmatch_t match[1];
    char **words = NULL;
    const char *p = str;
    int word_count = 0;
    
    if (regcomp(&regex, "[a-zA-Z]{4,}", REG_EXTENDED) != 0) {
        *count = 0;
        return NULL;
    }
    
    words = (char **)malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        regfree(&regex);
        *count = 0;
        return NULL;
    }
    
    while (regexec(&regex, p, 1, match, 0) == 0) {
        int len = match[0].rm_eo - match[0].rm_so;
        
        if (word_count >= MAX_WORDS || len >= MAX_WORD_LEN) {
            break;
        }
        
        words[word_count] = (char *)malloc((len + 1) * sizeof(char));
        if (words[word_count] == NULL) {
            int i;
            for (i = 0; i < word_count; i++) {
                free(words[i]);
            }
            free(words);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        
        strncpy(words[word_count], p + match[0].rm_so, len);
        words[word_count][len] = '\0';
        word_count++;
        
        p += match[0].rm_eo;
    }
    
    regfree(&regex);
    *count = word_count;
    return words;
}

void free_words(char **words, int count) {
    int i;
    if (words == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main() {
    char text[] = "This is a test string with several words of different lengths";
    char **words = NULL;
    int count = 0;
    int i;
    
    words = find_words(text, &count);
    
    if (words == NULL) {
        fprintf(stderr, "Error finding words\n");
        return 1;
    }
    
    printf("Found %d words with at least 4 characters:\n", count);
    for (i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
    
    free_words(words, count);
    
    return 0;
}