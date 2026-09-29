void swapNumbers(int* a, int* b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    int temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    *b = temp;
}