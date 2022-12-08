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

// 参考：https://wdv4758h-notes.readthedocs.io/zh_TW/latest/libunwind.html
void skip_func1() {
    unw_cursor_t cursor;
    unw_context_t uc;

    unw_getcontext(&uc);
    unw_init_local(&cursor, &uc);
    unw_step(&cursor);
    unw_resume(&cursor);
    std::cout << "skip_func1 will be skipped" << std::endl;
}

void skip_func2() {
    unw_cursor_t cursor;
    unw_context_t uc;

    unw_getcontext(&uc);
    unw_init_local(&cursor, &uc);
    unw_step(&cursor);
    unw_step(&cursor);
    unw_resume(&cursor);
    std::cout << "skip_func2 will be skipped" << std::endl;
}

void func1() {
    skip_func1();
    std::cout << "func1 will not be skipped" << std::endl;
}

void func2() {
    skip_func2();
    std::cout << "func2 will be skipped" << std::endl;
}

int main() {
    std::cout << "start" << std::endl;
    func1();
    std::cout << "func1 finished" << std::endl;
    func2();
    std::cout << "end" << std::endl;
    return 0;
}
