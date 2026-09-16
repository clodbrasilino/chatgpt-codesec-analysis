/* Possible weaknesses found:
 *  expected identifier or '(' before 'void'
 *  expected identifier or '('
 *  expected ')'
 *  to match this '('
 */
(void)setvbuf(stdout, NULL, _IONBF, 0);