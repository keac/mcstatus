#ifndef JINGJING_COLOR_HPP
#define JINGJING_COLOR_HPP

#ifndef __linux__
#error YOU MUST USE LINUX
#endif

#include <string>

namespace mc
{

class color
{
public:
    color();
    ~color();
    color(const char* s);
    color(const std::string& s);

    std::string toString() const;

    static color from_string(const std::string& s);
private:
    int minecraftcolor2sgr(char s);
    std::string mcColorToUnixColor(const std::string& msg);
private:
    std::string result;
};

} // namepsace mc

#endif // !JINGJING_COLOR_HPP
