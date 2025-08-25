#ifndef TIMEUTILS_UTILS_H
#define TIMEUTILS_UTILS_H

#include <chrono>
#include <string>
#include <iostream>

namespace timeutils {

using clock_t = std::chrono::steady_clock;
using time_point_t = clock_t::time_point;

inline time_point_t now() noexcept { return clock_t::now(); }

inline double elapsed_seconds(const time_point_t& start, const time_point_t& end) noexcept {
    return std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
}

inline double elapsed_milliseconds(const time_point_t& start, const time_point_t& end) noexcept {
    return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();
}

inline long long elapsed_microseconds(const time_point_t& start, const time_point_t& end) noexcept {
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Simple RAII timer: measure from construction (or reset) to query or destruction.
struct Timer {
    time_point_t start_time;
    Timer() noexcept : start_time(now()) {}
    void reset() noexcept { start_time = now(); }
    double seconds() const noexcept { return elapsed_seconds(start_time, now()); }
    double milliseconds() const noexcept { return elapsed_milliseconds(start_time, now()); }
    long long microseconds() const noexcept { return elapsed_microseconds(start_time, now()); }
};

// TimerGuard prints elapsed time on destruction. Default prints milliseconds to std::cerr.
struct TimerGuard {
    std::string label;
    time_point_t start_time;
    bool print_ms;
    explicit TimerGuard(const std::string& lbl = "", bool print_in_ms = true) noexcept
        : label(lbl), start_time(now()), print_ms(print_in_ms) {}
    ~TimerGuard() noexcept {
        auto end = now();
        if (print_ms) {
            std::cerr << label << (label.empty() ? "" : ": ") << elapsed_milliseconds(start_time, end) << " ms\n";
        } else {
            std::cerr << label << (label.empty() ? "" : ": ") << elapsed_seconds(start_time, end) << " s\n";
        }
    }
};

} // namespace timeutils

// Helper macros to create unique variable names for scope timing
#define TIMEUTILS_PASTE2(a, b) a##b
#define TIMEUTILS_PASTE(a, b) TIMEUTILS_PASTE2(a, b)

// Place this in a scope to automatically print elapsed time when scope exits:
//   TIME_BLOCK("my work");
#define TIME_BLOCK(label) timeutils::TimerGuard TIMEUTILS_PASTE(_timeutils_guard_, __COUNTER__)(label)

// Time a single statement or expression and print result immediately:
//   TIME_EXECUTE("call foo", foo());
// Use a stable pair of local variables inside the block. Each invocation
// is wrapped in its own do/while scope so the fixed names won't collide.
#define TIME_EXECUTE(label, stmt) \
    do { \
        const auto _timeutils_start = timeutils::now(); \
        (stmt); \
        const auto _timeutils_end = timeutils::now(); \
        std::cerr << (label) << ": " \
                  << timeutils::elapsed_milliseconds(_timeutils_start, _timeutils_end) \
                  << " ms\n"; \
    } while (0)

#endif // TIMEUTILS_UTILS_H