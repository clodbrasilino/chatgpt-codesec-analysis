#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **find_words_min_length_4(const char *text, size_t *out_count);
void free_words(char **words, size_t count);

/* Possible weaknesses found:
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  to match this '{'
 */
char **find_words_min_length_4(const char *text, size_t *out_count) {
    if (!text || !out_count) {
        return NULL;
    }

    *out_count = 0;

    regex_t regex;
    /* Possible weaknesses found:
     *  expected declaration or statement at end of input
     *  'REG_' undeclared (first use in this function)
     *  expected '}'
     *  to match this '('
     *  expected expression
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'REG_'
     *  expected ')'
     *  expected ')' at end of input
     */
    if (regcomp(&regex, "[a-zA-Z]{4,}", REG_