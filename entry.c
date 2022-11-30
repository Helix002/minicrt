/*
 * =================================================================
 *       Filename: entry.c
 *
 *    Description:
 *                 程序入口函数
 * =================================================================
 */

#include "minicrt.h"

extern int main(int argc, char **argv);
void myexit(int);

static void crt_fatal_error(const char* msg)
{
    myexit(1);
}

void mini_crt_entry(void)
{
    int ret;

    int argc;
    char **argv;

    char *ebp_reg = 0;

    asm volatile(
        "movl %%ebp, %0  \n\t"
        :"=m"(ebp_reg));   /* use =r fatal */

    argc = *(int *)(ebp_reg + 4);
    argv = (char **)(ebp_reg + 8);

    if(!mini_crt_heap_init())
        crt_fatal_error("heap initialize failed");
    if(!mini_crt_io_init())
        crt_fatal_error("IO initialize failed");

    ret = main(argc, argv);
    myexit(ret);
}

void myexit(int exitCode)
{
    asm volatile(
        "movl %0, %%ebx \n\t"
        "movl $1, %%eax \n\t"
        "int $0x80      \n\t"
        "hlt            \n\t"
        :
        :"m"(exitCode)
    );
}