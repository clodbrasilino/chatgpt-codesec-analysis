#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_ADVERB_LEN 50

typedef struct {
    char adverb[MAX_ADVERB_LEN];
    int position;
} AdverbMatch;

int find_adverbs(const char *sentence, AdverbMatch matches[], int max_matches) {
    regex_t regex;
    regmatch_t pmatch[2];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    int match_count = 0;
    int offset = 0;
    int ret;
    char *remaining;
    int sentence_len;
    
    if (sentence == NULL || matches == NULL || max_matches <= 0) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    sentence_len = strlen(sentence);
    remaining = strdup(sentence);
    if (remaining == NULL) {
        regfree(&regex);
        return 0;
    }
    
    while (match_count < max_matches && offset < sentence_len) {
        ret = regexec(&regex, remaining, 2, pmatch, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        }
        
        if (ret != 0) {
            break;
        }
        
        if (pmatch[0].rm_so >= 0 && pmatch[0].rm_eo > pmatch[0].rm_so) {
            int len = pmatch[0].rm_eo - pmatch[0].rm_so;
            
            if (len < MAX_ADVERB_LEN) {
                strncpy(matches[match_count].adverb, remaining + pmatch[0].rm_so, len);
                matches[match_count].adverb[len] = '\0';
                matches[match_count].position = offset + pmatch[0].rm_so;
                match_count++;
            }
        }
        
        offset += pmatch[0].rm_eo;
        
        if (pmatch[0].rm_eo >= strlen(remaining)) {
            break;
        }
        
        memmove(remaining, remaining + pmatch[0].rm_eo, strlen(remaining + pmatch[0].rm_eo) + 1);
    }
    
    free(remaining);
    regfree(&regex);
    
    return match_count;
}

int main(void) {
    const char *sentence = "The quickly running fox silently jumped over the lazy dog quietly.";
    AdverbMatch matches[MAX_MATCHES];
    int count;
    int i;
    
    count = find_adverbs(sentence, matches, MAX_MATCHES);
    
    printf("Sentence: %s\n", sentence);
    printf("Found %d adverbs:\n", count);
    
    for (i = 0; i < count; i++) {
        printf("  Adverb: '%s' at position %d\n", matches[i].adverb, matches[i].position);
    }
    
    return 0;
}