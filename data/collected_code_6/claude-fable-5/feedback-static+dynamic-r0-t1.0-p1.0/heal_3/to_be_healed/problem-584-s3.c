#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_SENTENCE_LEN 4096
#define ERRBUF_LEN 256

static void print_regex_error(int errcode, const regex_t *regex)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_LEN];
    size_t needed;

    memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(errcode, regex, errbuf, sizeof(errbuf));
    errbuf[sizeof(errbuf) - 1] = '\0';

    if (needed > sizeof(errbuf)) {
        fprintf(stderr, "Regex error (truncated): %s\n", errbuf);
    } else {
        fprintf(stderr, "Regex error: %s\n", errbuf);
    }
}

static int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    size_t offset;
    size_t len;
    int ret;
    int found;

    if (sentence == NULL) {
        return -1;
    }

    len = strnlen(sentence, MAX_SENTENCE_LEN);
    if (len >= MAX_SENTENCE_LEN) {
        fprintf(stderr, "Input sentence too long or not null-terminated.\n");
        return -1;
    }

    ret = regcomp(&regex, "[a-zA-Z]+ly", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex);
        return -1;
    }

    found = 0;
    offset = 0;

    while (offset < len) {
        ret = regexec(&regex, sentence + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            break;
        }

        {
            size_t start = offset + (size_t)match.rm_so;
            size_t end = offset + (size_t)match.rm_eo;

            if (end > len || start > end) {
                break;
            }

            if ((start == 0 || !isalpha((unsigned char)sentence[start - 1])) &&
                (end >= len || !isalpha((unsigned char)sentence[end]))) {
                printf("Adverb found: \"%.*s\" at position %zu\n",
                       (int)(end - start), sentence + start, start);
                found = 1;
            }

            if (end > offset) {
                offset = end;
            } else {
                offset += 1;
            }
        }
    }

    regfree(&regex);

    if (found == 0) {
        printf("No adverbs found.\n");
    }

    return 0;
}

int main(void)
{
    const char *sentence = "She quickly ran home and quietly opened the door, then slowly walked upstairs.";

    printf("Sentence: %s\n", sentence);

    if (find_adverbs(sentence) != 0) {
        fprintf(stderr, "Failed to process the sentence.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}