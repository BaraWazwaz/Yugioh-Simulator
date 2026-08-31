#include <fmt/core.h>
#include <fmt/ostream.h>
#include <yugioh/property.hpp>
#include <nitron/spec.hpp>

int main() {
    fmt::println(std::cout, "Hello, World!");

    nitron::Spec("property.hpp header")
    .add(yugioh::test::testModifier())
    .add(yugioh::test::testPipeline())
    .add(yugioh::test::testProperty())
    .report(std::cout);
    return 0;
}
