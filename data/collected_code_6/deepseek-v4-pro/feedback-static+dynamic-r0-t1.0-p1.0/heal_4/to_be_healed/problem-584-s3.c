#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char adverb[128];
    int position;
} AdverbInfo;

AdverbInfo *find_adverbs(const char *sentence, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    int ret;
    AdverbInfo *adverbs = NULL;
    int capacity = 0;
    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Either the condition 'count==NULL' is redundant or there is possible null pointer dereference: count. [nullPointerRedundantCheck]
     */
    *count = 0;
    const char *search_ptr = sentence;
    int offset = 0;

    /* Possible weaknesses found:
     *  Assuming that condition 'count==NULL' is not redundant
     */
    if (sentence == NULL || count == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret) {
        return NULL;
    }

    while (regexec(&regex, search_ptr, 2, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        int length = end - start;

        if (*count == capacity) {
            size_t new_capacity = (capacity == 0) ? 4 : (size_t)capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(AdverbInfo)) {
                free(adverbs);
                regfree(&regex);
                return NULL;
            }
            AdverbInfo *temp = realloc(adverbs, new_capacity * sizeof(AdverbInfo));
            if (!temp) {
                free(adverbs);
                regfree(&regex);
                return NULL;
            }
            adverbs = temp;
            capacity = (int)new_capacity;
        }

        if (length > 0 && (size_t)length < sizeof(adverbs[*count].adverb)) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(adverbs[*count].adverb, search_ptr + start, (size_t)length);
            adverbs[*count].adverb[length] = '\0';
            adverbs[*count].position = offset + start;
            (*count)++;
        }

        offset += matches[0].rm_eo;
        search_ptr += matches[0].rm_eo;
    }

    regfree(&regex);
    return adverbs;
}

int main(void) {
    const char *sentence = "She quickly ran very smoothly and happily through the park.";
    int count = 0;
    AdverbInfo *adverbs = find_adverbs(sentence, &count);

    if (adverbs) {
        printf("Adverbs found: %d\n", count);
        for (int i = 0; i < count; i++) {
            printf("  '%s' at position %d\n", adverbs[i].adverb, adverbs[i].position);
        }
        free(adverbs);
    } else if (count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Error processing regex.\n");
        return 1;
    }

    return 0;
}