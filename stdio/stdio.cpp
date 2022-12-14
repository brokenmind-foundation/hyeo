#include "stdio.h"


char* mem = 0x0;
void deleteOneCharacter(void){
    set_args(SYS_DELETEONECHARACTER,0,0,0);
    asm("int $110");
}
char* _ttyPrintInteger(int _integer){
    int i;
    char* txt = (char*)0x1000; 
    i = 0;
    do{
        txt[i++] = _integer % 10 + '0';
    } while((_integer /= 10) > 0);
    txt[i] = '\0';

    int lenght = (strlen(txt)-1);
    uint32_t a, b;
    uint8_t temp;
    for(a = 0,b = lenght; a < b; a++, b--){
        temp = txt[a];
        txt[a] = txt[b];
        txt[b] = temp;
    }

    return txt;
}
void set_args(char type, char arg1,char arg2, char arg3){
    mem[82] = type;
    mem[83] = arg1;
    mem[84] = arg2;
    mem[84] = arg3;
}
void print_char(char b){
    set_args(SYS_PRINT_CHAR,b,0,0);
    asm("int $110");
}
void readLine(char *data){
    int current = 0;
    char* copy = (char*)data;
    while(*data != '\0'){
        uint8_t b = readChar();
        if(b == 0x1C) break;
        if(b == 0x0E && current != 0){
            deleteOneCharacter();
            current--;
            data--;
        } else{
            b = ascii[b];
            *data = b;
            data++;
            current++;
            print_char(b);
        }
    }
    printf("\n");
    *data = '\0';
}
void clear(void){
    set_args(SYS_CLEAR_SCREEN,0,0,0);
    asm("int $110");
}
char readChar(void){
    set_args(SYS_READCHAR,0,0,0);
    asm("int $110");
    return *(char*)0x0;
}
void Sleep(uint32_t mill){
    set_args(SYS_SLEEP,0,0,0);
    int* b = (int*)0x0;
    *b = mill;
    asm("int $110");
}
void printf(const char* fmt, ...){
    int* argp = (int*)&fmt;
    argp += sizeof(fmt) / sizeof(int);
    uint8_t* ignored;
    uint8_t* data = (uint8_t*)fmt;
    while(*data != 0){
         switch (*data)
         {
            case '\n':
                set_args(SYS_NEW_LINE,0,0,0);
                asm("int $110");
                data++;
                break;
            case '%':
                switch (*(data + 1))
                {
                    case 'd':{
                        ignored = data +1;
                        printf(_ttyPrintInteger(*argp));
                        argp++;
                        break;
                    }
                    case 's': {
                        ignored = data+1;
                        printf(*(char**)argp);
                        argp++;
                        break;
                    }
                    case 'c': {
                        ignored = data+1;
                        print_char(*(char*)argp);
                        argp++;
                        break;
                    }
                    default:
                        print_char('%');
                        break;
                }
            default:
                if(ignored != data && ((*data != '%' && *(data + 1) != 'd')|| (*data != '%' && *(data + 1) != 's') || (*data != '%' && *(data + 1) != 'c')))   
                    print_char(*data);
                data++;  
                break;
        }
    }
}
void exit(int exit_code){

    set_args(SYS_PROCESS_EXIT,0,0,0);
    *(int*)0x0 = exit_code;
    asm("int $110");
    return;
}
void* memcpy(void* dest, void* src, uint32_t size){
    set_args(SYS_KERNEL_MEMCPY,0,0,0);
    int* mem = (int*)0x0;
    mem[0] = (int)dest;
    mem[1] = (int)src;
    mem[2] = size;
    asm("int $110");
}

void* memset(void* dest,uint8_t val, uint32_t size){
    set_args(SYS_KERNEL_MEMSET,0,0,0);
    uint32_t* mem = (uint32_t*)0x0;
    mem[0] = (uint32_t)dest;
    *(uint8_t*)(mem + 5) = val; 
    *(uint32_t*)(mem + 6) = size; 
    asm("int $110");
}