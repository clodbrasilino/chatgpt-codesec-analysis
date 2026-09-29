char* strrev(char* str) {
    if (!str || !*str)
        return str;

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