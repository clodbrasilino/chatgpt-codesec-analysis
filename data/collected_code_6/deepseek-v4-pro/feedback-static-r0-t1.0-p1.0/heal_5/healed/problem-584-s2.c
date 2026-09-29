#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_MATCHES 100
#define MAX_ADVERB_LEN 51

typedef struct {
    char adverb[MAX_ADVERB_LEN];
    int position;
} AdverbMatch;

static int safe_copy(char *dest, const char *src, size_t len, size_t max_len) {
    if (dest == NULL || src == NULL || max_len == 0) {
        return 0;
    }
    
    if (len >= max_len) {
        return 0;
    }
    
    if (len > 0) {
        size_t copy_len = len < (max_len - 1) ? len : (max_len - 1);
        memcpy(dest, src, copy_len);
        dest[copy_len] = '\0';
    } else {
        dest[0] = '\0';
    }
    
    return 1;
}

int find_adverbs(const char *sentence, AdverbMatch matches[], int max_matches) {
    regex_t regex;
    regmatch_t pmatch[2];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    int match_count = 0;
    int ret;
    size_t sentence_len;
    size_t offset;
    
    if (sentence == NULL || matches == NULL || max_matches <= 0) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    sentence_len = strlen(sentence);
    
    if (sentence_len > SIZE_MAX / 2) {
        regfree(&regex);
        return 0;
    }
    
    offset = 0;
    
    while (match_count < (size_t)max_matches && offset < sentence_len) {
        const char *search_start = sentence + offset;
        size_t search_len = sentence_len - offset;
        char *temp = NULL;
        
        if (search_len == 0) {
            break;
        }
        
        temp = (char *)malloc(search_len + 1);
        if (temp == NULL) {
            break;
        }
        
        memcpy(temp, search_start, search_len);
        temp[search_len] = '\0';
        
        ret = regexec(&regex, temp, 2, pmatch, 0);
        
        if (ret == REG_NOMATCH) {
            free(temp);
            break;
        }
        
        if (ret != 0) {
            free(temp);
            break;
        }
        
        if (pmatch[0].rm_so >= 0 && pmatch[0].rm_eo > pmatch[0].rm_so) {
            regoff_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            
            if ((size_t)pmatch[0].rm_eo <= search_len) {
                if (match_len > 0 && (size_t)match_len < MAX_ADVERB_LEN) {
                    if (safe_copy(matches[match_count].adverb, 
                                 temp + pmatch[0].rm_so, 
                                 (size_t)match_len, 
                                 MAX_ADVERB_LEN)) {
                        matches[match_count].position = (int)(offset + (size_t)pmatch[0].rm_so);
                        match_count++;
                    }
                }
            }
            
            offset += (size_t)pmatch[0].rm_eo;
            free(temp);
        } else {
            free(temp);
            break;
        }
    }
    
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