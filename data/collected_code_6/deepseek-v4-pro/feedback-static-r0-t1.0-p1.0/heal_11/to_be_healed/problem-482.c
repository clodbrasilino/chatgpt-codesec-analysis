#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t match;
    const char *pattern = "[A-Z][a-z]+";
    const char *cursor = str;
    int ret;

    if (str == NULL) {
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        size_t errbuf_size = regerror(ret, &regex, NULL, 0);
        char *errbuf = (char *)malloc(errbuf_size);
        if (errbuf) {
            regerror(ret, &regex, errbuf, errbuf_size);
            fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
            free(errbuf);
        }
        return;
    }

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        int start = match.rm_so;
        int end = match.rm_eo;
        
        if (start == -1 || end == -1) {
            break;
        }
        
        /* Possible weaknesses found:
         *  Assuming that condition 'end<=start' is not redundant
         */
        if (end <= start) {
            cursor += (*cursor != '\0') ? 1 : 0;
            if (*cursor == '\0') {
                break;
            }
            continue;
        }
        
        /* Possible weaknesses found:
         *  Assignment 'len=(unsigned long)(end-start)', assigned value is greater than 0
         */
        size_t len = (size_t)(end - start);
        
        char *seq = (char *)malloc(len + 1);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (!seq) {
            regfree(&regex);
            return;
        }
        
        /* Possible weaknesses found:
         *  Condition 'len>0' is always true [knownConditionTrueFalse]
         *  Condition 'len>0' is always true
         */
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(seq, cursor + start, len);
        }
        seq[len] = '\0';
        printf("%s\n", seq);
        free(seq);
        
        cursor += end;
        if (*cursor == '\0') {
            break;
        }
    }

    regfree(&regex);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    find_sequences(argv[1]);
    return EXIT_SUCCESS;
}