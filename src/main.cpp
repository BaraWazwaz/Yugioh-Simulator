#include <string>
#include <fmt/core.h>
#include <yugioh/card.hpp>

int main() {
    using namespace std::string_literals;

    yugioh::Card dark_magician ("Dark Magician"s, "some url"s);
    fmt::print("{}: {}\n", dark_magician.name(), dark_magician.imageURL());
    return 0;
}
