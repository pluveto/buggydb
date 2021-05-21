#include <buggydb/value_interface.hpp>
#include <string>
namespace buggydb
{
    class string_value : value_interface
    {
    private:
        // int capicity;
        // int free;
        // char buf[];
        std::string str;

    public:
        size_t size(){
            return str.size();
        }
        char *serialize()
        {
            return str.c_str();
        }
    }
}