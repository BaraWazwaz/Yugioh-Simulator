#include <nitron/spec.hpp>
#include <yugioh/property.hpp>

namespace yugioh::test {

void testProperty() {
    using namespace nitron;

    class FakeAdd : public Modifier<int> {
        ValueType pass(ValueType previous) const override { return previous + 10; }
    };
    class FakeMult : public Modifier<int> {
        ValueType pass(ValueType previous) const override { return previous * 2; }
    };

    Spec("property.hpp")
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Property<int> temp(100);
            return temp.getValue();
        },
        [](int x) -> bool { return x == 100; },
        "Baseline: Empty pipeline returns initial value"
    ))
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Property<int> temp(5);
            temp.addModifier(std::make_unique<FakeAdd>());
            temp.addModifier(std::make_unique<FakeMult>());
            return temp.getValue();
        },
        [](int x) -> bool { return x == 30; },
        "Pipeline Execution: Modifiers calculate sequentially"
    ))
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Property<int> temp(10);
            auto it1 = temp.addModifier(std::make_unique<FakeAdd>());  
            temp.addModifier(std::make_unique<FakeMult>());
            temp.removeModifier(it1);
            return temp.getValue();
        },
        [](int x) -> bool { return x == 20; },
        "Lifecycle: Removing a modifier correctly updates the pipeline output"
    ))
    .displayResult(std::cout);
}

} // namespace yugioh::test
