void decimalToOctal(int decimal){
    int octal[100];
    int i = 0;
    
    while(decimal > 0){
        octal[i] = decimal % 8;
        decimal /= 8;
        i++;
    }
    
    for(int j = i - 1; j >= 0; j--){
        printf("%d", octal[j]);
    }
}