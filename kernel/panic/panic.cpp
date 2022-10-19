#include "panic.h"


void panic(const char* sys_message){
    _printf(" \n#--System Crashed! - not syncing--#\n");
    _printf("\n%s\n", sys_message);
    _printf("\n#--end of kernel panic - not syncing--#\n");
    asm("cli");
    for(;;)
        asm("hlt");
}