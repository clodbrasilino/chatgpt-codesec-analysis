#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

void find_adverbs(const char *sentence) {
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;

    ret = regcomp(&regex, "\\b[a-zA-Z]+ly\\b", REG_EXTENDED);
    if (ret != 0) {
        regfree(&regex);
        return;
    }

    while (1) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (offset >= strlen(sentence)) {
            break;
        }

        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        
        if (ret != 0) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        size_t adverb_start = offset + match.rm_so;
        size_t adverb_len = match.rm_eo - match.rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t sentence_len = strlen(sentence);

        if (adverb_len > 0 && adverb_start < sentence_len) {
            char *adverb = malloc(adverb_len + 1);
            if (adverb != NULL) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
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
    char *sentence = malloc(256);
    if (sentence == NULL) {
        return 1;
    }
    
    snprintf(sentence, 256, "He quickly ran and then suddenly stopped.");

    find_adverbs(sentence);

    free(sentence);
    return 0;
}