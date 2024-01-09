int arithmeticSum(int firstTerm, int difference, int numTerms) {
    int sum = 0;
    for (int i = 0; i < numTerms; i++) {
        sum += firstTerm;
        firstTerm += difference;
    }
    return sum;
}