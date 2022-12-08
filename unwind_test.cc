#include <iostream>
#include <stdio.h>

using namespace std;

// libunwind的编译过程：
// autoreconf -i
// ./configure
// make
// make install
//
#include "libunwind.h"


// 参考代码：
void show_backtrace() {
    unw_cursor_t cursor;
    unw_context_t uc;
    unw_word_t ip, sp;

#define BUF_SZ 4096
    char buf[BUF_SZ];
    unw_word_t offset;
    unw_getcontext(&uc);    // store registers
    unw_init_local(&cursor, &uc); // initialize with context

    std::cout << "++++++++++++++++" << std::endl;
    while (unw_step(&cursor) > 0) {
        unw_get_reg(&cursor, UNW_REG_IP, &ip);
        unw_get_reg(&cursor, UNW_REG_SP, &sp);
        unw_get_proc_name(&cursor, buf, BUF_SZ, &offset);
        printf("0x%016lx <%s+0x%lx>\n", ip, buf, offset);
    }
    std::cout << "++++++++++++++++" << std::endl;
}

void func() {
    show_backtrace();
}

int main() {
    std::cout << "1" << std::endl;
    show_backtrace();
    std::cout << "2" << std::endl;
    func();
    std::cout << "3" << std::endl;
    show_backtrace();
    std::cout << "4" << std::endl;
    return 0;
}
