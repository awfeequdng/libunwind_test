#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sys/ptrace.h>

using namespace std;

// libunwind的编译过程：
// autoreconf -i
// ./configure
// make
// make install
//
#include "libunwind.h"
#include "libunwind-ptrace.h"

unw_addr_space_t as;

void die(std::string msg) {
    std::cout << msg << std::endl;
    exit(0);
}

void show_backtrace(int pid) {

    if (ptrace(PTRACE_ATTACH, pid, 0, 0) != 0) {
        die("ERROR: cannot attach to " + to_string(pid));
    }

    unw_cursor_t cursor;
    void *uc = _UPT_create(pid);
    if (unw_init_remote(&cursor, as, uc) != 0) {
        die("ERROR: cannot initialize cursor for remote unwinding");
    }

    do {
        unw_word_t offset, pc;
        char sym[4096];
        if (unw_get_reg(&cursor, UNW_REG_IP, &pc))
            die("ERROR: cannot read program counter");

        printf("0x%lx: ", pc);
        if (unw_get_proc_name(&cursor, sym, 4096, &offset) == 0) {
            printf("(%s+0x%lx)\n", sym, offset);
        } else {
            printf("-- no symbol name found\n");
        }
    } while(unw_step(&cursor) > 0);

    _UPT_destroy(uc);
    (void)ptrace(PTRACE_DETACH, pid, 0, 0);
}

int main(int argc, char **argv) {

    as = unw_create_addr_space(&_UPT_accessors, 0);
    std::cout << "start " << std::endl;
    auto pid = atoi(argv[1]);
    show_backtrace(pid);
    std::cout << "end " << std::endl;
    return 0;
}
