#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

void find_adverbs(const char *sentence, size_t sentence_len) {
    if (sentence == NULL || sentence_len == 0) {
        return;
    }

    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;

    ret = regcomp(&regex, "\\b[a-zA-Z]+ly\\b", REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return;
    }

    while (offset < sentence_len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH || ret != 0 || match.rm_so == -1) {
            break;
        }

        size_t adverb_start = offset + match.rm_so;
        size_t adverb_len = match.rm_eo - match.rm_so;

        if (adverb_len > 0 && adverb_start < sentence_len && adverb_len <= sentence_len && (adverb_start + adverb_len) <= sentence_len) {
            char *adverb = malloc(adverb_len + 1);
            if (adverb != NULL) {
                memcpy(adverb, sentence + adverb_start, adverb_len);
                adverb[adverb_len] = '\0';
                printf("Adverb: %s, Position: %zu\n", adverb, adverb_start);
                free(adverb);
            }
        }

        if (match.rm_eo > 0) {
            offset += match.rm_eo;
        } else {
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    size_t buffer_size = 256;
    char *sentence = malloc(buffer_size);
    if (sentence == NULL) {
        return 1;
    }
    
    snprintf(sentence, buffer_size, "He quickly ran and then suddenly stopped.");

    size_t sentence_len = strnlen(sentence, buffer_size);
    find_adverbs(sentence, sentence_len);

    free(sentence);
    return 0;
}