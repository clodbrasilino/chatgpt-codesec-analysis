/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
char* strrev(char* str) {
    if (!str || !*str)
        return str;

    /* Possible weaknesses found:
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     *  incompatible implicit declaration of built-in function 'strlen' [-Wbuiltin-declaration-mismatch]
     *  include '<string.h>' or provide a declaration of 'strlen'
     */
    int i = strlen(str) - 1, j = 0;

    char ch;
    while(i > j) {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}