int highestPowerOfTwo(int n) {
    int power = 0;
    while (n > 1) {
        n = n / 2;
        power++;
    }
    return (1 << power);
}