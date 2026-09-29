/* Possible weaknesses found:
 *  expected '=', ',', ';', 'asm' or '__attribute__' before '<' token
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 *  expected '=', ',', ';', 'asm' or '__attribute__' before '++' token
 *  expected identifier or '(' before 'for'
 *  expected identifier or '('
 */
for (size_t i = 0U; i < len - 1U; i++) {