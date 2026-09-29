#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100
#define MAX_ADVERB_LEN 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char adverb[MAX_ADVERB_LEN];
    int position;
} AdverbMatch;

static int safe_copy(char *dest, const char *src, int len, int max_len) {
    if (len < 0 || len >= max_len) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'dest!=NULL' is not redundant
     */
    if (len > 0 && src != NULL && dest != NULL) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, (size_t)len);
    }
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'dest!=NULL' is redundant or there is possible null pointer dereference: dest. [nullPointerRedundantCheck]
     */
    dest[len] = '\0';
    return 1;
}

int find_adverbs(const char *sentence, AdverbMatch matches[], int max_matches) {
    regex_t regex;
    regmatch_t pmatch[2];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    int match_count = 0;
    int ret;
    char *remaining;
    size_t sentence_len;
    size_t remaining_len;
    size_t offset;
    
    if (sentence == NULL || matches == NULL || max_matches <= 0) {
        return 0;
    }
    
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    sentence_len = strlen(sentence);
    if (sentence_len > (size_t)(-1) / 2) {
        regfree(&regex);
        return 0;
    }
    
    remaining = strdup(sentence);
    if (remaining == NULL) {
        regfree(&regex);
        return 0;
    }
    
    remaining_len = sentence_len;
    offset = 0;
    
    while (match_count < max_matches && offset < sentence_len) {
        if (remaining_len == 0) {
            break;
        }
        
        ret = regexec(&regex, remaining, 2, pmatch, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        }
        
        if (ret != 0) {
            break;
        }
        
        if (pmatch[0].rm_so >= 0 && pmatch[0].rm_eo > pmatch[0].rm_so) {
            int len = pmatch[0].rm_eo - pmatch[0].rm_so;
            
            if ((size_t)pmatch[0].rm_so < remaining_len && (size_t)pmatch[0].rm_eo <= remaining_len) {
                if (safe_copy(matches[match_count].adverb, remaining + pmatch[0].rm_so, len, MAX_ADVERB_LEN)) {
                    matches[match_count].position = (int)(offset + (size_t)pmatch[0].rm_so);
                    match_count++;
                }
            }
        }
        
        if ((size_t)pmatch[0].rm_eo >= remaining_len) {
            break;
        }
        
        offset += (size_t)pmatch[0].rm_eo;
        remaining_len -= (size_t)pmatch[0].rm_eo;
        
        if (remaining_len > 0) {
            memmove(remaining, remaining + pmatch[0].rm_eo, remaining_len);
            remaining[remaining_len] = '\0';
        } else {
            remaining[0] = '\0';
            remaining_len = 0;
        }
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