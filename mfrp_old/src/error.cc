#include "error.h"
#include <cstdio>

namespace mfrp {

char* Slprintf(char* buf, const char* last, const char* fmt, ...) noexcept
{
    va_list args;

    va_start(args, fmt);
    buf = Vslprintf(buf, last, fmt, args);
    va_end(args);

    return buf;
}

char* Vslprintf(char* buf, const char* last, const char* fmt, va_list args) noexcept
{
    int len = 0;
    int size = last - buf;

    if (size > 0) {
        len = std::vsnprintf(buf, size, fmt, args);
        if (len >= size)
            len = size - 1;
    }

    /* discard error */
    return len > 0 ? buf + len : buf;
}


Error::Error(const char* fmt, ...) noexcept
{
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(msg_, sizeof(msg_), fmt, args);
    va_end(args);
}

}
