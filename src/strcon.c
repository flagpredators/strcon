#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "file_handler.h"
#include "validate.h"

char slash = '/', end = 0;

char *basename(char const *path){

    char *s = strrchr(path, slash);
    if(!s) 
        return strdup(path);
    else 
        return strdup(s + 1);

}

int octal_to_string(char *octdump, char* file_out){

    FILE* fptr = init(file_out);
    char *token = strtok(octdump, " ");
    
    while( token != NULL ) {
        
        if(validateOctalValue(token) == -1) {
            fprintf(stderr, "ValueError: detected incorrect octal value.");
            putchar(end);
            return 1;

        }

	char ch = octToDec(_strtoi(token));
        fputc(ch, fptr);

        token = strtok(NULL, " ");
    }
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);

    return 0;
    }


int decimal_to_string(char *intdump, char* file_out){

    FILE* fptr = init(file_out);       
    
    if(validateIntValue(intdump) == -1) {
        fprintf(stderr, "ValueError: incorrect value detected.");
        putchar(end);
        return 1;
    }  
    
    char *token = strtok(intdump, " ");
    
    while( token != NULL ) {  

        char ch  = _strtoi(token);
        fputc(ch, fptr);

        token = strtok(NULL, " ");
    }
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);


    return 0;
}


int binary_to_string(char *bindump, char* file_out){

    FILE* fptr = init(file_out);
    char *token = strtok(bindump, " ");
    int ch;
    
    while( token != NULL ) {

        ch = validateBinValue(token); 
        if(ch == -1) {
            fprintf(stderr, "ValueError: detected incorrect binary value.");
            putchar(end);
            return 1;

        } else if(ch == -2) {
            fprintf(stderr, "ValueError: binary value's greater than expected.");
            putchar(end);
            return 1;
        }
        fputc((char)ch, fptr);

        token = strtok(NULL, " ");
    }
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);


    return 0;
}


int hexadecimal_to_string(char *hexdump, char* file_out){

    FILE* fptr = init(file_out);

    if(validateHexValue(hexdump) == -1) {
        fprintf(stderr, "ValueError: detected incorrect hex value.");
        putchar(end);
        exit(1);   

    }

    char *token = strtok(hexdump, " ");
    while( token != NULL ) {

        char ch = hexToDec(token);
        fputc(ch, fptr);

        token = strtok(NULL, " ");
    }
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);


    return 0;
}


int stringToDecimal(char* string, char* file_out){

    FILE* fptr = init(file_out);

    for(size_t i = 0; i < strlen(string); ++i){

        fprintf(fptr, "%d ", string[i]);
    }    
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);

    return 0;
}

int stringToOctal(char* string, char* file_out){

    FILE* fptr = init(file_out);

    for(size_t i = 0; i < strlen(string); ++i){

        fprintf(fptr, "%o ", string[i]);
    }    
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);

    return 0;
}

int stringToHexadecimal(char* string, char* file_out){

    FILE* fptr = init(file_out);

    for(size_t i = 0; i < strlen(string); ++i){

        fprintf(fptr, "0x%x ", string[i]);
    }    
    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);

    return 0;
}

int stringToBinary(char* string, char* file_out){

    FILE* fptr = init(file_out);

    for(size_t i = 0; i < strlen(string); ++i){

        char* bin = decToBin(string[i]);
        fprintf(fptr, "%s ", bin);
        free(bin);
    }    

    if(fptr == stdout)
        putchar(end);
    else
        fclose(fptr);

    return 0;
}


void usage(char* param){
    fprintf(stderr, "\nUsage: %s <type|conversion> <input> [ data | file ] -o outfile.txt\n", param);
}

void help(){
    fprintf(stdout, "\n|CLI options|:-\
    \n   type/conversion:\
    \n      -O  converts octal dump to string.\
    \n      -B  converts binary dump to string.\
    \n      -D  converts decimal dump to string.\
    \n      -X  converts hexadecimal dump to string.\
    \n          [if -s flag is specified, it converts string to <type>.]\
    \n\n   input:\n      -i  takes next argument as data string.\
    \n      -f  takes next argument as filename.\
    \n\n   optional:\n      -o  takes next argument as filename.\
    \n\t  (if filename is not given, default is strcon_out.)\n\n");
}


int arg_validate(char* arg){
    if(arg == NULL || 
        !strcmp(arg, "-X") ||
        !strcmp(arg, "-B") || 
        !strcmp(arg, "-O") || 
        !strcmp(arg, "-D") || 
        !strcmp(arg, "-f") ||
        !strcmp(arg, "-i") ||
        !strcmp(arg, "-o") ||
        !strcmp(arg, "-s")){
            return -1;
        }
    return 0;
}

int main(int argc, char**argv){

    #ifdef _WIN32
        end = 0;
        slash = '\\';
    #elif __unix__
        end = 10;
        slash = '/';
    #endif

    char *opt_hd = "-X", *opt_bd = "-B", *opt_od = "-O", *opt_id = "-D", 
         *opt_f = "-f", *opt_o = "-o", *opt_i = "-i", *opt_tostr = "-s";
    char *out_file = NULL, type[5]; 
    char *storage, *exe = basename(argv[0]);
    int i = 0, opt_f_stat = 0, opt_i_stat = 0, type_stat = 0, opt_tostr_stat = 0;

    if(argc == 2 && !strcmp(argv[1], "-h")){
        usage(exe);
        help();
        memoff(&exe);
        return -1;


    } else if(argc >= 4 && argc <= 7){

        for(; i < argc; i++){
            if(!strcmp(argv[i], opt_tostr)){
                opt_tostr_stat = 1;
            }
        }
        
        for(i = 0;i < argc; i++){
                if(!strcmp(argv[i], opt_f)){

                    opt_f_stat = 1;
                    if(arg_validate(argv[i+1]) == -1){
                        fprintf(stderr, "\nInputError: file not detected.\n");
                        usage(exe);
                        fprintf(stderr, "\nFor more, check help section:\
                        \n    %s -h\n\n", exe);
                        memoff(&exe);
                        return -1;

                    }
                    storage = read_t(argv[i+1], opt_tostr_stat);
                    break;
                } else{
                    continue;
                }
            }


        for(i = 0; i < argc; i++){
            if(!strcmp(argv[i], opt_i)){

                opt_i_stat = 1;
                if(arg_validate(argv[i+1]) == -1){
                    fprintf(stderr, "\nInputError: no input detected.\n");
                    usage(exe);
                    fprintf(stderr, "\nFor more, check help section:\
                    \n    %s -h\n\n", exe);
                    memoff(&exe);
                    return -1;

                }
                storage = argv[i+1];

                if(opt_f_stat && opt_i_stat){
                    usage(exe);
                    help();
                    memoff(&exe);
                    return -1;

                }
        
            } else{
                continue;
            }
        }

        for(i = 0; i < argc; i++){
            if(!strcmp(argv[i], opt_o)){

                if(arg_validate(argv[i+1]) == -1){
                    out_file = "strcon_out";
                } else {
                    out_file = argv[i+1];
                }
                break;
            } else{
                continue;
            }
        }
        
        for(i = 0; i < argc; i++){
            if(!strcmp(argv[i], opt_hd)){
                strcpy(type, opt_hd);
                type_stat++;
            }
        }
        for(i = 0; i < argc; i++){
            if(!strcmp(argv[i], opt_bd)){
                strcpy(type, opt_bd);
                type_stat++;
            }
        }
        for(i = 0; i < argc; i++){
            if(!strcmp(argv[i], opt_od)){
                strcpy(type, opt_od);
                type_stat++;
            }
        }
        for(i = 0; i < argc; i++){
            if(!strcmp(argv[i], opt_id)){
                strcpy(type, opt_id);
                type_stat++;
            }
        }


        if(type_stat > 1){
            fprintf(stderr, "\nTypeError: data can't be of more than one type.\n");
            help();
            return -1;
        } else if(type_stat == 0){
            fprintf(stderr, "\nTypeError: data type not specified!\n");
            help();
            return -1;
        }
        
    } else{
        usage(exe);
        fprintf(stderr, "\nFor more, check help section:\
        \n    %s -h\n\n", exe);
        memoff(&exe);
        return -1;

    }


    if(opt_f_stat == 0 && opt_i_stat == 0){
        fprintf(stderr, "\nInputError: no data or file detected.\n");
        help();
        return -1;
    } else if(opt_tostr_stat) {

        if(!strcmp(type, opt_od))
            stringToOctal(storage, out_file);
        else if(!strcmp(type, opt_hd))
            stringToHexadecimal(storage, out_file);
        else if(!strcmp(type, opt_bd))
            stringToBinary(storage, out_file);
        else if(!strcmp(type, opt_id))
            stringToDecimal(storage, out_file);
    } else {
        if(!strcmp(type, opt_od))
            octal_to_string(storage, out_file);
        else if(!strcmp(type, opt_hd))
            hexadecimal_to_string(storage, out_file);
        else if(!strcmp(type, opt_bd))
            binary_to_string(storage, out_file);
        else if(!strcmp(type, opt_id))
            decimal_to_string(storage, out_file);
        else    
            return -1;
        
    }
    memoff(&exe);
    if(opt_f_stat)
        memoff(&storage);
    
    return 0;
}