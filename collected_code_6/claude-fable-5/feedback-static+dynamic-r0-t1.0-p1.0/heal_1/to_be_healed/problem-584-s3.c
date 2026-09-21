#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int find_adverbs(const char *sentence)
{
    regex_t regex;
    regmatch_t match;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[256];
    size_t offset;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    size_t start;
    /* Possible weaknesses found:
     *  The scope of the variable 'end' can be reduced. [variableScope]
     */
    size_t end;
    int ret;
    int found;

    if (sentence == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(sentence);

    ret = regcomp(&regex, "[a-zA-Z]+ly", REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
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
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "Regex execution failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        start = offset + (size_t)match.rm_so;
        end = offset + (size_t)match.rm_eo;

        if ((start == 0 || !isalpha((unsigned char)sentence[start - 1])) &&
            (end >= len || !isalpha((unsigned char)sentence[end]))) {
            printf("Adverb found: \"%.*s\" at position %zu\n",
                   (int)(end - start), sentence + start, start);
            found = 1;
        }

        if (match.rm_eo > match.rm_so) {
            offset = end;
        } else {
            offset += 1;
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