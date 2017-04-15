#include "mcstatus/color.hpp"

#include <string>
#include <memory>
#include <iostream>
#include <cctype>
#include <cstdarg>
#include <boost/algorithm/string.hpp>

namespace
{

std::string format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

} // namespace

namespace mc
{

color::color()
{
}

color::~color()
{
    
}

color::color(const char* s)
{
    *this = from_string(s);
}

color::color(const std::string& s)
{
    *this = from_string(s);
}

std::string color::toString() const
{
    return result;
}

int color::minecraftcolor2sgr(char s)
{
    int sgr = 0;
    switch (s)
    {
        case '0':
            sgr = 30;
            break;
        case '1':
            sgr = 34;
            break;
        case '2':
            sgr = 32;
            break;
        case '3':
            sgr = 36;
            break;
        case '4':
            sgr = 31;
            break;
        case '5':
            sgr = 35;
            break;
        case '6':
            sgr = 33;
            break;
        case '7':
            sgr = 37;
            break;
        case '8':
            sgr = 37;
            break;
        case '9':
            sgr = 34;
            break;
        case 'a':
            sgr = 32;
            break;
        case 'b':
            sgr = 36;
            break;
        case 'c':
            sgr = 31;
            break;
        case 'd':
            sgr = 35;
            break;
        case 'e':
            sgr = 33;
            break;
        default:
            break;
    }

    return sgr;
}

std::string color::mcColorToUnixColor(const std::string& msg)
{
    std::string buffer = msg;

    for (int size = msg.find("§"); size <= msg.rfind("§"); size = msg.find("§", size+1))
    {
        std::string old;
        std::string to;
        for (int i = size; i < size+3; i++)
            old += msg.at(i);
        if (minecraftcolor2sgr(msg.at(size+2)) != 0)
            to = format("\x1b[%dm", minecraftcolor2sgr(msg.at(size+2)));
        else
            to = "\033[0m";
        buffer = boost::replace_all_copy(buffer, old, to);
    }

    return buffer;
}

color color::from_string(const std::string& s)
{
    color color_new;

    color_new.result = color_new.mcColorToUnixColor(s);
    color_new.result += "\033[0m";
    //std::cout << s[s.find("§")+2] << std::endl;

    return color_new;
}

}
