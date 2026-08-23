#include <fmt/core.h>
#include <fmt/color.h>

int main() {
    fmt::print("Hello, Yu-Gi-Oh Simulator Developer!\n");
    fmt::print("Testing framework version: {} (Released: {})\n", 11.0, 2024);    
    fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "✅ Success: fmt library is working flawlessly!\n");
    return 0;
}
