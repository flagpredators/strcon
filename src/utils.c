#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

int power(int base, int p){ 
    int result = 1;
    if(p){ 
        for(int i = p; i > 0; i--){ 
            result *= base;
        }
    }
    return result;
}

void* allocate(size_t _Count, size_t _Size) {
    void* tmp = calloc(_Count, _Size);
    if(tmp == NULL) 
        exit(EXIT_FAILURE);
    return tmp;
}

void* reallocate(void* _Buffer, size_t _Size) {
    void* tmp = realloc(_Buffer, _Size);
    if(tmp == NULL) 
        exit(EXIT_FAILURE);
    return tmp;
}

int _strtoi(const char* str){ //changes number stored in a string to integer
    int res = 0;
    char *ptr = (char*)str;

    while (*ptr != '\0') {
        if (isdigit(*ptr)) {
            res *= 10; 
            res += *ptr++ - 48; 
        }
    }
    return res;
}

void _strrev_(char*str){
   
    int len = strlen(str), i = 0, j = len-1;
    while(i < j){
        char temp  = *(str+i);
        *(str+(i++)) = *(str+j);
        *(str+(j--)) = temp;
    }
}

int octToDec(int n){
    int dec = 0, oct = n, count = 0;

    while(oct){ 
        count++; 
        oct = oct/10; 
    }

    oct = n; 
    for(int i = 0; i <= count; i++){
        dec += (oct % 10) * power(8, i); 
        oct = oct/10; 
    }

    return dec;
}

int hexToDec(char* h){ 

    int dec = 0, bitshift = 0, cnt = 0;
    char* ptr = h; 

    while(*ptr != '\0'){ 
        cnt++; 
        ptr++; 
    }

    while(cnt >= 0){ 
        --cnt;
        if((*(h+cnt) >=97 && *(h+cnt) <=102)) 
            dec += (*(h+cnt)-87)*power(16, bitshift); 
        else if((*(h+cnt) >=65 && *(h+cnt) <=70)) 
            dec += (*(h+cnt)-55)*power(16, bitshift); 
        else if((*(h+cnt) >=48 && *(h+cnt) <=57)) 
            dec += (*(h+cnt)-48)*power(16, bitshift);; 
        bitshift++; 
    }

    return dec;
}


int binToDec(char* binary){ 
    
    int cnt = strlen(binary), dec = 0;

    for(int j = cnt-1, k = 0; j >= 0; --j, ++k)
        dec += (binary[k] - 48) * power(2, j); 

    return dec;
}

char* decToBin(int n){ 
    
    unsigned int dec = n;
    char binary[9];
    int i = 0;

    while(dec){ 

        int remain = dec % 2; 
        binary[i++] = remain+48; 
        dec = dec/2; 
    }
    binary[i] = '\0';
    
    while(strlen(binary) != 8){
        binary[i++] = '0'; 
    }

    binary[i] = '\0';
    _strrev_(binary);

    return strdup(binary);
    
}

void memoff(char** alloc_mem) {

    free(*alloc_mem);
    *alloc_mem = NULL;
}


