#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

const int HEX_FORMAT = 1;
const int DEC_FORMAT = 2;
const int HEX_BASE = 16;

int checkType(char value[]);
int convertToDecimal(char value[]);
int calculateBaseTimesPower(int counter, int base);
int calculateDivider(int value, int base);
char* calculateDivision(int value, int divider, int base);
char convertToDictionary(int digit);
char convertToHex(int value, int base);\

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

char convertToDictionary(int digit) {
    const char HEXA_ARR[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    for (int i = 0; i < sizeof(HEXA_ARR); i++) {
        if (digit == i) {
            return HEXA_ARR[i];
        }
    }
}

char* calculateDivision(int value, int divider, int base) {
    int remainder;
    char* res = (char*) malloc(10 * sizeof(char));
    char strDigit[6];
    char convertedDigit;

    int digit = value / divider;
    convertedDigit = convertToDictionary(digit);
    strncat(res, &convertedDigit, 1);
    remainder = value % divider;
    divider = divider/base;

    while (divider > 0) {
        digit = remainder / divider;
        remainder = remainder % divider;
        divider /= base;
        convertedDigit = convertToDictionary(digit);
        strncat(res, &convertedDigit, 1);
    }
    printf("%s\n", res);
    return res;
}

int calculateDivider(int value, int base) {
    int baseCopy = base;
    while (baseCopy*base <= value) {
        baseCopy *= base;
    }
    return baseCopy;
}

char convertToHex(int value, int base) {
    int divider = calculateDivider(value, base);
    char* res = calculateDivision(value, divider, base);
    printf("%s", res);
    return value;
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

int convertToDecimal(char value[]) {
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
    return sum;
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
    int inputArray[] = {669};
    char mystr[10];
    sprintf(mystr, "%d", inputArray[0]);
    char hexStr[5] = "100";

    /*
    char* msg = "Hello World";
    printf("%0xd\n", msg);
    char c = *(msg + 2);
    printf("%c", c);
    */

    int valueFormat = checkType(mystr);
    if (valueFormat == HEX_FORMAT) {
        int result = convertToDecimal(hexStr);
        printf("Converted Value is %d", result);
    } else {
        convertToHex(inputArray[0], HEX_BASE);
    }
}
