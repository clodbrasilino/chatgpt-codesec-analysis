#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_line(FILE *fp)
/* Possible weaknesses found:
 *  to match this '{'
 */
{
    size_t capacity = 128;
    size_t len = 0;
    char *line;
    int c;
    int got_any = 0;

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  to match this '{'
     */
    while ((c = fgetc(fp)) != EOF) {
        got_any = 1;
        if (c == '\n') {
            break;
        }
        /* Possible weaknesses found:
         *  to match this '{'
         *  Unmatched '{'. Configuration: ''. [syntaxError]
         */
        if (len + 1 >= capacity) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'capac'
             *  each undeclared identifier is reported only once for each function it appears in
             *  expected ',' or ';' at end of input
             *  expected ';' at end of declaration
             *  expected declaration or statement at end of input
             *  'capac' undeclared (first use in this function); did you mean 'capacity'?
             *  expected '}'
             */
            size_t new_capacity = capac