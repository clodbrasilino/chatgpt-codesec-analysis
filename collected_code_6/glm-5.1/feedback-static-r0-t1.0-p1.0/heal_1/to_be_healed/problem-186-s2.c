#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals(const char *haystack, const char **literals, size_t count, regmatch_t **matches, size_t *match_count) {
    regex_t regex;
    /* Possible weaknesses found:
     *  The scope of the variable 'ret' can be reduced. [variableScope]
     */
    int ret;
    size_t capacity = 16;
    size_t m_count = 0;
    regmatch_t *m_arr = malloc(capacity * sizeof(regmatch_t));
    if (m_arr == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(literals[i]);
        if (len == 0) {
            free(m_arr);
            return -1;
        }

        char *escaped = malloc(len * 2 + 1);
        if (escaped == NULL) {
            free(m_arr);
            return -1;
        }

        size_t e_len = 0;
        for (size_t j = 0; j < len; j++) {
            char c = literals[i][j];
            switch (c) {
                case '^': case '.': case '[': case '$':
                case '(': case ')': case '|': case '*':
                case '+': case '?': case '{': case '\\':
                    escaped[e_len++] = '\\';
                    break;
            }
            escaped[e_len++] = c;
        }
        escaped[e_len] = '\0';

        ret = regcomp(&regex, escaped, REG_EXTENDED);
        free(escaped);

        if (ret != 0) {
            free(m_arr);
            return -1;
        }

        const char *curr = haystack;
        while (1) {
            regmatch_t match;
            ret = regexec(&regex, curr, 1, &match, 0);
            if (ret == REG_NOMATCH) {
                break;
            }
            if (ret != 0) {
                regfree(&regex);
                free(m_arr);
                return -1;
            }

            if (m_count >= capacity) {
                capacity *= 2;
                regmatch_t *temp = realloc(m_arr, capacity * sizeof(regmatch_t));
                if (temp == NULL) {
                    regfree(&regex);
                    free(m_arr);
                    return -1;
                }
                m_arr = temp;
            }

            m_arr[m_count].rm_so = (curr - haystack) + match.rm_so;
            m_arr[m_count].rm_eo = (curr - haystack) + match.rm_eo;
            m_count++;

            if (match.rm_eo == 0) {
                curr++;
            } else {
                curr += match.rm_eo;
            }

            if (*curr == '\0') {
                break;
            }
        }
        regfree(&regex);
    }

    *matches = m_arr;
    *match_count = m_count;
    return 0;
}

int main(void) {
    const char *text = "The cost is $100.00, not $50.00 or 100.00.";
    const char *literals[] = {"$100.00", "$50.00", "100.00"};
    size_t count = sizeof(literals) / sizeof(literals[0]);

    regmatch_t *matches = NULL;
    size_t match_count = 0;

    int result = search_literals(text, literals, count, &matches, &match_count);

    if (result == 0) {
        for (size_t i = 0; i < match_count; i++) {
            printf("Match %zu: start=%lld, end=%lld, substring='%.*s'\n",
                   i,
                   (long long)matches[i].rm_so,
                   (long long)matches[i].rm_eo,
                   (int)(matches[i].rm_eo - matches[i].rm_so),
                   text + matches[i].rm_so);
        }
    } else {
        printf("Search failed.\n");
    }

    free(matches);
    return 0;
}