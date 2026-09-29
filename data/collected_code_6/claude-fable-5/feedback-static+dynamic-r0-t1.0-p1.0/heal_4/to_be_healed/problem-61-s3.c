/* Possible weaknesses found:
 *  'max_len' undeclared here (not in a function)
 *  's' undeclared here (not in a function)
 *  implicit declaration of function 'strnlen' [-Wimplicit-function-declaration]
 *  type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
 *  call to undeclared function 'strnlen'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
 *  use of undeclared identifier 'max_len'
 *  type defaults to 'int' in declaration of 'n' [-Wimplicit-int]
 *  use of undeclared identifier 's'
 */
n = strnlen(s, max_len);
/* Possible weaknesses found:
 *  syntax error: keyword 'if' is not allowed in global scope [syntaxError]
 *  expected identifier or '(' before 'if'
 *  expected identifier or '('
 */
if (n >= max_len) {
    return -1;
}