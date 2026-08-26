#include <nitron/spec.hpp>

#include <yugioh/property.hpp>

namespace yugioh
{

void test_property() {
    using namespace nitron;

    class FakeModifier1 : public Modifier<int> {
        ValueType pass(ValueType previous) const override {
            return previous + 10;
        }
    };
    class FakeModifier2 : public Modifier<int> {
        ValueType pass(ValueType previous) const override {
            return previous / 3;
        }
    };
    class FakeModifier3 : public Modifier<int> {
        ValueType pass(ValueType previous) const override {
            return previous * 5;
        }
    };

    Spec("property.hpp")
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Property<int> temp (5);
            temp.addModifier(std::make_unique<FakeModifier1>());
            temp.addModifier(std::make_unique<FakeModifier2>());
            temp.addModifier(std::make_unique<FakeModifier3>());
            return temp.getValue();
        },
        [](int x) -> bool { return x == 25; },
        "5 +10 /3 *5 => 25"
    ))
    .displayResult(std::cout);
}

} // namespace yugioh
