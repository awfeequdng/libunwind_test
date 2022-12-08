#include <iostream>
#include <sys/ucontext.h>
#include <ucontext.h>

using namespace std;

struct layout {
    layout* rbp;
    void* ret;
};

// 栈帧结构参考：
// https://www.cnblogs.com/Chang-LeHung/p/16907670.html

void func1() {
    std::cout << "enter func1" << std::endl;
    ucontext_t uc;
    layout *rbp = (layout*)__builtin_frame_address(0);
    rbp = rbp->rbp;
    getcontext(&uc);
    uc.uc_mcontext.gregs[REG_RIP] = (unsigned long)rbp->ret;
    uc.uc_mcontext.gregs[REG_RBP] = (unsigned long)rbp->rbp;
    setcontext(&uc);
    std::cout << "func1 will be skipped" << std::endl;
}

void skip_func() {
    func1();
    std::cout << "skip_func skipped" << std::endl;
}


int main() {
    std::cout << "start main" << std::endl;
    skip_func();
    std::cout << "end main" << std::endl;

    // 程序退出时会coredump，这是什么原因？？？
    return 0;
}