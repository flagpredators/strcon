
#pragma once


//Function declarations
void* allocate(size_t _Count, size_t _Size);
void* reallocate(void* _Buffer, size_t _Size);
int octToDec(int oct);
int hexToDec(char* hex);
int binToDec(char* bin);
int power(int base, int exp);
int _strtoi(const char* str);
void _strrev_(char*str);
char* decToBin(int n);
void memoff(char** alloc_mem);


