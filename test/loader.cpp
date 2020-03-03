#include <dynalo/dynalo.hpp>

#include <cstdint>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include "shared.hpp"


// usage: loader "path/to/shared/lib/dir" [function_ptr/function]
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("usage: loader \"path / to / shared / lib / dir\" [function_ptr/function]");
        return 1;
    }

    dynalo::library lib(std::string(argv[1]) + "/" + dynalo::to_native_name("shared"));

    std::ostringstream oss;
    oss << "it works: ";

    if (strcmp(argv[2], "function") == 0)
    {
        auto add_integers  = lib.get_function<int32_t(const int32_t, const int32_t)>("add_integers");
        auto print_message = lib.get_function<void(const char*)>("print_message");
    
        oss << "<std::function mode> 1 + 2 = " << add_integers(1, 2);
        print_message(oss.str().c_str());

    }
    else if (strcmp(argv[2], "function_ptr") == 0)
    {
        auto add_integers = lib.get_function_ptr<add_integers_fn>("add_integers");
        auto print_message = lib.get_function_ptr<print_message_fn>("print_message");
        
        oss << "<function pointer mode> 1 + 2 = " << add_integers(1, 2);
        print_message(oss.str().c_str());
    }
}
