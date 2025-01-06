// tiny-glog logging library implementation with RAII in mind
// - line-level anonymouse instance
// - sink log in destructor
// - stream-style logging with operator<<() function
#include <iostream>
#include <sstream>

class Logger
{
public:
    Logger(const char* tag, const char* file, int line) {
        stream << tag << " " << file << ":" << line << " ";
    }
    ~Logger() {
        std::cerr << stream.str() << '\n';
    }
    std::stringstream stream;
};

#define LOGD Logger("[D]", __FILE__, __LINE__).stream
#define LOGE Logger("[E]", __FILE__, __LINE__).stream

int main()
{
    LOGD << "Hello" << " World";
    LOGD << "Hello" << " C++";
    return 0;
}

