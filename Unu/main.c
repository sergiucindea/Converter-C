#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const int HEX_FORMAT = 1;
const int DEC_FORMAT = 2;

int checkType(char value[]);
void convertToDecimal(char value[]);
char trimValue(char value[]);
char trim(char value[]);
char removeElement(char value[], char c);
int calculateBaseTimesPower(int counter, int base);

/*
char trimValue(char value[]) {
    const char HEX_CHARS[] = {'x', 'X', '#'};
    for (int i = 0; i < sizeof(HEX_CHARS); i++) {

        char *src, *dst;
        for (src = dst = value; *src != '\0'; src++) {
            *dst = *src;
            if (*dst != HEX_CHARS[i]) dst++;
        }
        *dst = '\0';

    }
    return value;
}
*/

void convertToHex(char value[]) {

}

int calculateBaseTimesPower(int power, int base) {
    int baseCopy = 1;
    if (power == 0) {
        return baseCopy;
    } else {
        for (int i = 0; i < power; i++) {
            baseCopy *= base;
        }
    }
    return baseCopy;
}

void convertToDecimal(char value[]) {
    const char HEXA_ARR[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    const int HEX_BASE = 16;
    int digit = 0;
    int sum = 0;
    int power = strlen(value) - 1;
    for (int i = 0; i < strlen(value) ; i++) {
        for (int j = 0; j < sizeof(HEXA_ARR); j++) {
            if (value[i] == HEXA_ARR[j]) {
            digit = j;
            int baseRaised = calculateBaseTimesPower(power, HEX_BASE);
            sum += digit * baseRaised;
            break;
            }
        }
        power--;
    }
    printf(">>%d<<", sum);
}

int checkType(char value[]) {
    const char HEX_VAL[9] = {'a', 'b', 'c', 'd', 'e', 'f', 'x', '#'};
    int valueType;
    for (int i = 0; i < strlen(HEX_VAL); i++) {
        if (strchr(value, HEX_VAL[i]) != NULL) {
            valueType = HEX_FORMAT;
            break;
        } else {
            valueType = DEC_FORMAT;
        }
    }
    return valueType;
}

int main() {
    //int inputArray[] = {12256};
    //char mystr[10];
    //sprintf(mystr, "%d", inputArray[0]);

    char hexStr[5] = "f64";
    int valueFormat = checkType(hexStr);
    if (valueFormat == HEX_FORMAT) {
    //convert to dec
        convertToDecimal(hexStr);
    } else {
        convertToHexa(hexStr);
    //convert to Hexa
    }
}
