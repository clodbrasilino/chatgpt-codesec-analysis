/* Possible weaknesses found:
 *  syntax error: keyword 'if' is not allowed in global scope [syntaxError]
 *  expected identifier or '(' before 'if'
 *  expected identifier or '('
 */
if (setvbuf(stdout, NULL, _IONBF, 0) != 0) {
    return EXIT_FAILURE;
}