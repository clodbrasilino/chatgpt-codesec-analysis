/* Possible weaknesses found:
 *  expected declaration specifiers or '...' before '&' token
 *  expected ')'
 *  expected parameter declarator
 *  expected function body after function declarator
 *  syntax error [syntaxError]
 *  to match this '('
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  unknown type name 'argv'
 *  expected declaration specifiers or '...' before string constant
 */
sscanf(argv[1], "%u %c", &n, &extra) != 1