#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>
#include <errno.h>

#define MAX_MATCHES 100
#define MAX_ADVERB_LEN 51

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char adverb[MAX_ADVERB_LEN];
    int position;
} AdverbMatch;

static int safe_copy(char *dest, size_t dest_size, const char *src, size_t src_len) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return 0;
    }
    
    if (src_len >= dest_size) {
        return 0;
    }
    
    if (src_len > 0) {
        size_t copy_len = src_len < (dest_size - 1) ? src_len : (dest_size - 1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, src, copy_len);
        dest[copy_len] = '\0';
    } else {
        dest[0] = '\0';
    }
    
    return 1;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len >= max_len) {
        if (str[len] != '\0') {
            return max_len;
        }
    }
    
    return len;
}

int find_adverbs(const char *sentence, AdverbMatch matches[], int max_matches) {
    regex_t regex;
    regmatch_t pmatch[2];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    int match_count = 0;
    size_t offset;
    
    if (sentence == NULL || matches == NULL || max_matches <= 0) {
        return 0;
    }
    
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return 0;
    }
    
    size_t sentence_len = safe_strlen(sentence, SIZE_MAX >> 1);
    if (sentence_len == 0 || sentence_len >= (SIZE_MAX >> 1)) {
        regfree(&regex);
        return 0;
    }
    
    if (sentence_len > SIZE_MAX / 2) {
        regfree(&regex);
        return 0;
    }
    
    offset = 0;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'offset<sentence_len' is not redundant
     */
    while (match_count < (size_t)max_matches && offset < sentence_len) {
        const char *search_start = sentence + offset;
        /* Possible weaknesses found:
         *  Assignment 'search_len=sentence_len-offset', assigned value is greater than 0
         */
        size_t search_len = sentence_len - offset;
        
        /* Possible weaknesses found:
         *  Condition 'search_len==0' is always false
         *  Condition 'search_len==0' is always false [knownConditionTrueFalse]
         */
        if (search_len == 0) {
            break;
        }
        
        char *temp = (char *)malloc(search_len + 1);
        if (temp == NULL) {
            break;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp, search_start, search_len);
        temp[search_len] = '\0';
        
        ret = regexec(&regex, temp, 2, pmatch, 0);
        
        if (ret == REG_NOMATCH) {
            free(temp);
            break;
        }
        
        if (ret != 0) {
            free(temp);
            regfree(&regex);
            return match_count;
        }
        
        if (pmatch[0].rm_so >= 0 && pmatch[0].rm_eo > pmatch[0].rm_so) {
            regoff_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
            
            if ((size_t)pmatch[0].rm_eo <= search_len) {
                if (match_len > 0 && (size_t)match_len < MAX_ADVERB_LEN) {
                    if (safe_copy(matches[match_count].adverb,
                                 MAX_ADVERB_LEN,
                                 temp + pmatch[0].rm_so,
                                 (size_t)match_len)) {
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