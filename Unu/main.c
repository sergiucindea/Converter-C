#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

const int HEX_FORMAT = 1;
const int DEC_FORMAT = 2;
const int HEX_BASE = 16;
const int BIN_BASE = 2;
const char HEXA_ARR[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '\0'};
const char HEX_VAL[] = {'a', 'b', 'c', 'd', 'e', 'f', 'x', '#', '\0'};
char HEX_SYMBOLS[] = {'x', 'X', '#'};

char* convertDigitToBinary(int value, char* result) {

    if (value > 1) {
        convertDigitToBinary(value/2, result);
    }

    if (value%2 == 1) {
        strcat(result, "1");
    } else {
        strcat(result, "0");
    }

    return result;
}

char* convertToBinary(char* value) {
    int bin[10];
    char* hexDigit = (char*) malloc(5 * sizeof(char));
    for (int i = 0; i < strlen(value); i++) {
        for (int j = 0; j < strlen(HEXA_ARR); j++) {
            if (value[i] == HEXA_ARR[j]) {
                hexDigit = convertDigitToBinary(j, hexDigit);
                //strcat(res, hexDigit);
                break;
            }
        }
    }
    return hexDigit;
}

char convertToDictionary(int digit) {
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

char* convertToHex(int value, int base) {
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

char* trim(char* value) {
    char* trimmed = (char*) malloc(5 * sizeof(char));
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


int convertToDecimal(char* value) {
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

int checkType(char* value) {
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
    int inputArray[] = {12265};
    char inputAsString[10];
    sprintf(inputAsString, "%d", inputArray[0]);
    char* hexValue;
    char* hexStr = "x9f";

    printf("The original value is: %s\n", hexStr);
    int valueFormat = checkType(inputAsString);
    if (valueFormat == HEX_FORMAT) {
        int result = convertToDecimal(hexStr);
        hexValue = trim(hexStr);
        printf("Converted Value is: %d\n", result);
    } else {
        char* result = convertToHex(inputArray[0], HEX_BASE);
        hexValue = result;
        printf("Converted Value is: %s\n", result);
    }
    char *binResult = convertToBinary(hexValue);
    printf("%s", binResult);
    free(hexValue);
    free(binResult);
}
