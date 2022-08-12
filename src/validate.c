#include <string.h>
#include<stdio.h>
#include <ctype.h>

#include "utils.h"

int validateOctalValue(char*octal_value) {

    /* Octal values can't have the value 8 and 9,
       so searches for them, if present
       it returns -1 */
    if(strcspn(octal_value, "89") != strlen(octal_value)){
        return -1;
    }
    return 0;
}

int validateHexValue(char*hex_value) {

    /* Hex values can't have values other than
       "123456789ABCDEF" */
    if(strspn(hex_value, "0123456789ABCDEFabcdefxX \n") != strlen(hex_value)){
        return -1;
    }
    return 0;
}

int validateIntValue(char*int_value) {

    for (int i = 0; int_value[i] != '\0'; i++){
        if(int_value[i] == ' ' || int_value[i] == '\n')
            continue;

        if (!isdigit(int_value[i])){
            return -1;
        }
    }

    return 0;
}

int validateBinValue(char*bin_value) {

    /* Binary values can't have values other 
       than 0 and 1 */

    size_t len = strlen(bin_value);
    if(strspn(bin_value, "01") != len && len != 8)
        return -1;

    int dec = binToDec(bin_value); 
    if(dec > 126)
        return -2;

    return dec;
}
