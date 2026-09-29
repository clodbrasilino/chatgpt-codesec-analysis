#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

typedef struct {
    char *adverb;
    int position;
} AdverbInfo;

static AdverbInfo *find_adverbs(const char *sentence, int *count) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "\\b[A-Za-z]+ly\\b";
    int ret;
    AdverbInfo *adverbs = NULL;
    int capacity = 0;
    const char *search_ptr;
    int offset;

    if (sentence == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    search_ptr = sentence;
    offset = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (ret) {
        return NULL;
    }

    while (regexec(&regex, search_ptr, 2, matches, 0) == 0) {
        int start = matches[0].rm_so;
        int end = matches[0].rm_eo;
        size_t length;

        if (end <= start) {
            offset += matches[0].rm_eo;
            search_ptr += matches[0].rm_eo;
            continue;
        }

        length = (size_t)(end - start);

        if (*count == capacity) {
            size_t new_capacity = (capacity == 0) ? 4 : (size_t)capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(AdverbInfo)) {
                for (int i = 0; i < *count; i++) {
                    free(adverbs[i].adverb);
                }
                free(adverbs);
                regfree(&regex);
                return NULL;
            }
            AdverbInfo *temp = realloc(adverbs, new_capacity * sizeof(AdverbInfo));
            if (!temp) {
                for (int i = 0; i < *count; i++) {
                    free(adverbs[i].adverb);
                }
                free(adverbs);
                regfree(&regex);
                return NULL;
            }
            adverbs = temp;
            capacity = (int)new_capacity;
        }

        adverbs[*count].adverb = malloc(length + 1);
        if (!adverbs[*count].adverb) {
            for (int i = 0; i < *count; i++) {
                free(adverbs[i].adverb);
            }
            free(adverbs);
            regfree(&regex);
            return NULL;
        }

        if (length > 0) {
            memcpy(adverbs[*count].adverb, search_ptr + start, length);
        }
        adverbs[*count].adverb[length] = '\0';
        adverbs[*count].position = offset + start;
        (*count)++;

        offset += matches[0].rm_eo;
        search_ptr += matches[0].rm_eo;
    }

    regfree(&regex);
    return adverbs;
}

int main(void) {
    const char *sentence = "She quickly ran very smoothly and happily through the park.";
    int count;
    AdverbInfo *adverbs = find_adverbs(sentence, &count);

    if (adverbs) {
        printf("Adverbs found: %d\n", count);
        for (int i = 0; i < count; i++) {
            printf("  '%s' at position %d\n", adverbs[i].adverb, adverbs[i].position);
            free(adverbs[i].adverb);
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