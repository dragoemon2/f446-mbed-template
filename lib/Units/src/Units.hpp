#include <chrono>

inline std::chrono::microseconds operator ""_hz(unsigned long long value) {
    return std::chrono::microseconds(1000000) / value;
}
