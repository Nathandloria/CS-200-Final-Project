#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "calculator.c"

int decToBin(int);
int binToDec(int);
int hexToBin(char*);
char* binToHex(int);
int decToHex(int);
int hexToDec(char*);

int binToDec(int bin) {
    int dec = 0;
    for (int i = 0; bin; i++, bin /= 10) {
    if (bin % 10)
        dec += pow(2, i);
    }
    return dec;
}

int decToBin(int dec) {
    int decimal = 0;
    int bit = getBits(dec);
    unsigned long res = 0;

    do {
        if (dec / (int)pow(2, bit) == 1) {
            res += ceil(pow(10, bit));
            dec -= pow(2, bit);
        }
        bit--;
    } while (dec != 0);

    return res;
}

int hexToBin(char* hex){
    // Returns the binary equivalent of a hexadecimal value
    long int i = 0;

    while (*(hex +i)){
        switch (*(hex +i)){
            case '0':
                if (i == 0){
                    printf(""); break;
                }
                else{
                    printf("0000"); break;
                }
            case '1':
                if (i == 0){
                    printf("1"); break;
                }
                else {
                    printf("0001"); break;
                }
            case '2':
                if (i == 0){
                    printf("10"); break;
                }
                else{
                    printf("0010"); break;
                }
            case '3':
                if (i == 0){
                    printf("11"); break;
                }
                else {
                    printf("0011"); break;
                }
            case '4':
                if (i == 0){
                    printf("100"); break;
                }
                else{
                    printf("0100"); break;
                }
            case '5':
                if (i == 0){
                    printf("101"); break;
                }
                else{
                    printf("0101"); break;
                }

            case '6':
                if (i == 0){
                    printf("110"); break;
                }
                else{
                    printf("0110"); break;
                }
            case '7':
                if (i == 0){
                    printf("111"); break;
                }
                else{
                    printf("0111"); break;
                }
            case '8':
                printf("1000"); break;
            case '9':
                printf("1001"); break;
            case 'A':
                printf("1010"); break;
            case 'B':
                printf("1011"); break;
            case 'C':
                printf("1100"); break;
            case 'D':
                printf("1101"); break;
            case 'E':
                printf("1110"); break;
            case 'F':
                printf("1111"); break;
            case 'a':
                printf("1010"); break;
            case 'b':
                printf("1011"); break;
            case 'c':
                printf("1100"); break;
            case 'd':
                printf("1101"); break;
            case 'e':
                printf("1110"); break;
            case 'f':
                printf("1111"); break;
            default:
                printf("\n Invalid hex digit %c ", *(hex +i));
                return 0;
        }
        i++;
    }
}

char* binToHex(int bin){
    int j = 0;
    int rem = bin;
    printf("%d", bin);

    int len = 0;

    do {
        rem /= 10000;
        len++;
    } while ( rem != 0);

    char* hex = malloc(sizeof(char) * len);

    int i = 1;
    while (bin != 0) {
        rem += (bin % 10) * pow(2, j);
        j++;
        printf("\nrem: %d\n", rem);
        if (rem < 10) {
            *(hex + len - i) = 48 + rem;
            printf("%c\n", *(hex + len - i));
            if (bin / 10 == 0 && j <= 3)
                i++;
        } else {
            *(hex + len - i) = 87 + rem;
            printf("%c\n", *(hex + len - i));
        }
        if (!(j %= 4)) {
            i++;
            rem = 0;
        }

        bin = bin / 10;
    }
    *(hex + i - 1) = '\0';
    return hex;
}

int decToHex(int dec){
    // Returns a string containing the hex
    char hex[1000];
    int i = 0;
    int rem = dec;

    while(dec != 0){
        rem = dec % 16;
        if(rem < 10){
            hex[i++] = 48 + rem;
        }
        else{
            hex[i++] = 55 +rem;
        }
        dec /= 16;
    }
    printf("0x");

    for(int j = i - 1; j >= 0; j--){
        printf("%c", hex[j]);
    }
}

int hexToDec(char* hex){
    printf("%d", strlen(hex));
    int num = 0;
    switch (*(hex)){
        case '1':num = 1;break;
        case '2':num = 2;break;
        case '3':num = 3;break;
        case '4':num = 4;break;
        case '5':num = 5;break;
        case '6':num = 6;break;
        case '7':num = 7;break;
        case '8':num = 8;break;
        case '9':num = 9;break;
        case 'a':num = 10;break;
        case 'b':num = 11;break;
        case 'c':num = 12;break;
        case 'd':num = 13;break;
        case 'e':num = 14;break;
        case 'f':num = 15;break;
        default:;
    }
    if ( strlen(hex) -1 == 0)
        return num;
    return num * pow(16, strlen(hex) -1) + hexToDec( hex + 1);
}

