int findMostSignificantSetBit(int num) {
    int msb = 0;
  
    while (num != 0) {
        num = num >> 1;
        msb++;
    }
  
    return (1 << (msb - 1));
}