#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

const int HEX_FORMAT = 1;
const int DEC_FORMAT = 2;
const int HEX_BASE = 16;

int checkType(char value[]);
int convertToDecimal(char value[]);
int calculateBaseTimesPower(int counter, int base);
int calculateDivider(int value, int base);
char *calculateDivision(int value, int divider, int base);
char convertToDictionary(int digit);
char *convertToHex(int value, int base);
char *trim(char *value);

char convertToDictionary(int digit) {
    const char HEXA_ARR[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    for (int i = 0; i < sizeof(HEXA_ARR); i++) {
        if (digit == i) {
            return HEXA_ARR[i];
        }
    }
}

char *calculateDivision(int value, int divider, int base) {
    int remainder;
    char *res = (char*) malloc(10 * sizeof(char));
    char strDigit[6];
    char convertedDigit;

    if (value < base) {
        convertedDigit = convertToDictionary(value);
        strncat(res, &convertedDigit, 1);
    } else {
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

        //free(res);
        return res;
    }
}

int calculateDivider(int value, int base) {
    int baseCopy = base;
    while (baseCopy*base <= value) {
        baseCopy *= base;
    }
    return baseCopy;
}

char *convertToHex(int value, int base) {
    int divider = calculateDivider(value, base);
    return calculateDivision(value, divider, base);
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

char *trim(char *value) {
    char *trimmed = (char*) malloc(5 * sizeof(char));

    /*
    for (int i = 0; i < sizeof(value); i++) {
        printf("%c", value[i]);
    }
    */

    const char HEX_SYMBOLS[5] = {'x', 'X', '#'};
    for (int i = 0; i < strlen(value); i++) {
        int OK = 1;
        for (int j = 0; j < strlen(HEX_SYMBOLS); j++) {
            if (value[i] != HEX_SYMBOLS[j]){
                if((j == strlen(HEX_SYMBOLS)-1) && OK) {
                    strncat(trimmed, &value[i], 1);
                }
            } else {
                OK = 0;
            }
        }
    }
    return trimmed;
}

int convertToDecimal(char *value) {
    const char HEXA_ARR[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    int digit = 0;
    int sum = 0;
    char *trimmed = trim(value);
    int power = strlen(trimmed) - 1;
    for (int i = 0; i < strlen(trimmed) ; i++) {
        for (int j = 0; j < strlen(HEXA_ARR); j++) {
            if (trimmed[i] == HEXA_ARR[j]) {
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

int checkType(char *value) {
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
    int inputArray[] = {5};
    char inputAsString[10];
    sprintf(inputAsString, "%d", inputArray[0]);
    int arrSize = 5;
    //char hexStr[5] = "#100";

    char *hexStr = (char*) malloc(5 * sizeof(char));
    hexStr = "#1000";

    int valueFormat = checkType(hexStr);
    if (valueFormat == HEX_FORMAT) {
        int result = convertToDecimal(hexStr);
        printf("Converted Value is \"%d\"", result);
    } else {
        char *result = convertToHex(inputArray[0], HEX_BASE);
        printf("Converted Value is \"%s\"", result);
    }
}
