#include <fmt/core.h>
#include <fmt/ostream.h>
#include <yugioh/property.hpp>

int main() {
    fmt::println(std::cout, "Hello, World!");
    yugioh::test::testModifier().displayResult(std::cout);
    yugioh::test::testPipeline().displayResult(std::cout);
    yugioh::test::testProperty().displayResult(std::cout);
    return 0;
}
