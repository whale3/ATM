#ifndef _ERROR_H
#define _ERROR_H

#include <exception>
#include <cstdarg>

namespace mfrp {

char* Slprintf(char* buf, const char* last, const char* fmt, ...) noexcept;
char* Vslprintf(char* buf, const char* last, const char* fmt, va_list args) noexcept;

class Error : public std::exception {
public:
    Error() = default;

    explicit Error(const char* fmt, ...) noexcept;

    const char* what() const noexcept override
    { return msg_; }

protected:
    char msg_[1024] = {'\0'};
};

}

#endif
