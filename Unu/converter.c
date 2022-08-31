#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

const int HEX_FORMAT = 1;
const int DEC_FORMAT = 2;
const int HEX_BASE = 16;
const int BIN_BASE = 2;

const char* HEXA_ARR = "0123456789abcdef";
const char* HEX_VAL = "abcdefx#";
const char* HEX_SYMBOLS = "xX#";

typedef struct{
    void (*convert)(char* inputValue);
} Converter;

int checkFormat(char* value) {
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
   //free(trimmed);
   return sum;
}

char* addDigitAsBinToStr(int digit, char* string) {

   if (digit > 1) {
       addDigitAsBinToStr(digit/2, string);
   }

   if (digit%2 == 1) {
       strcat(string, "1");
   } else {
       strcat(string, "0");
   }

   return string;
}

char* convertToBinary(char* value) {
   char* binDigitStr = (char*) malloc(5 * sizeof(char));
   for (int i = 0; i < strlen(value); i++) {
       for (int j = 0; j < strlen(HEXA_ARR); j++) {
           if (value[i] == HEXA_ARR[j]) {
               if (j == 0) {
                   strcat(binDigitStr, "0000");
                   break;
               }
               else if (j == 1) {
                   strcat(binDigitStr, "000");
               } else if (j < 4) {
                   strcat(binDigitStr, "00");
               } else if (j < 8) {
                   strcat(binDigitStr, "0");
               }
               binDigitStr = addDigitAsBinToStr(j, binDigitStr);
           }
       }
   }
   return binDigitStr;
}

char convertToDictionary(int digit) {
   for (int i = 0; i < strlen(HEXA_ARR); i++) {
       if (digit == i) {
           return HEXA_ARR[i];
       }
   }
}

char* calculateDivision(int value, int divider, int base) {
   int remainder;
   char* res = (char*) malloc(10 * sizeof(char));
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

void convert(char* inputValue) {
    char* hexValue;
    int valueFormat = checkFormat(inputValue);
    if (valueFormat == HEX_FORMAT) {
        hexValue = trim(inputValue);
        int result = convertToDecimal(inputValue);
        printf("Converted value is %d\n", result);
    } else {
        int inputAsInt = atoi(inputValue);
        hexValue = convertToHex(inputAsInt, HEX_BASE);
        printf("Converted value is %s\n", hexValue);
    }

    char* binResult = convertToBinary(hexValue);
    printf("Converted binary value is %s", binResult);
    free(hexValue);
    free(binResult);
}

Converter newConverter(void) {
    Converter conv;
    conv.convert = &convert;
    return conv;
}
