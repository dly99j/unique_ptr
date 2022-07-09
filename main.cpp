#include <iostream>
#include "unique_ptr.h"

int main() {
    auto deleter = [](auto&& val){
        std::cout << "deleted\n";
        delete val;
    };
    mstl::unique_ptr ptr(new int, deleter);
    return 0;
}
