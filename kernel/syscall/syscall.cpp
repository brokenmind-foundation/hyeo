#include "syscall.h"



void sys_call_init(void){
    set_call_handler();
}
void set_call_handler(void){
    set_idt_gate(110,(uint32_t)call_handler);
}
void syscall(void){
    char* mem = 0x0;
    syscall_handler(mem[82],mem[83],mem[84],mem[85]);
}
void call_handler(void){
    syscall();
}

void syscall_handler(char type, char argv1, char argv2, char argv3){
    char* mem = 0x0;
    sti(); // enable interrupts
    switch (type)
    {
    case SYS_CLEAR_SCREEN:
        clear_screen();
        break;
    case SYS_PRINT_CHAR:
        print_char(argv1,VGA_WHITEGRAY);
        break;
    case SYS_NEW_LINE:
        printf("\n");
        break;
    case SYS_PRINT_INTEGER:
        _ttyPrintInteger(*((int*)mem));
        break;
    case SYS_PROCESS_EXIT:
        _printf("\n\nProcess Exited with %d\n", *(int*)0x0);
        break;
    case SYS_RANDOM:
        break;

    case SYS_READCHAR: {
        char* b = (char*)0x0;
        *b = readChar();
        break;
    }
    case SYS_DELETEONECHARACTER: {
        deleteOneCharacter();
        break;
    }
    case SYS_SLEEP:{
        Sleep(*(int*)0x0);
        break;
    }
    case SYS_BOOT_SECONDS:{
        uint32_t* b = (uint32_t*)0x10;
        *b = getSeconds();
        break;
    }
    case SYS_KERNEL_MEMCPY:{
        uint32_t* mem = (uint32_t*)0x0;
        uint32_t* dest = (uint32_t*)mem[0]; 
        uint32_t* src = (uint32_t*)mem[1];
        uint32_t size = mem[2]; 
        memcpy(dest,src,size);
        break;
    }
    case SYS_KERNEL_MEMSET:{
        uint32_t* mem = (uint32_t*)0x0;
        void* dest = (void*)mem[0]; 
        uint8_t val = *(mem + 5);
        uint32_t size = *(uint32_t*)(mem + 6); 
        memset(dest,val,size);
        break;
    }
    case SYS_CRASH:{
        panic("Panic generated by manual.");
        break;
    }
    case SYS_HFS_GET_DATA:{
        int* ptr = 0x0;
        HFS_INIT* hfs = get_hfs_data();
        *ptr = (uint32_t)hfs;
        break;
    }
    default:
        break;
    }
}