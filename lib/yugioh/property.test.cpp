#include <yugioh/property.hpp>

namespace yugioh::test {

nitron::Spec testModifier() {
    using namespace nitron;
    using StringModifier = Modifier<std::string>;

    struct Quote : public StringModifier {
        ValueType pass(ValueType previous) const override {
            return std::string("\"") + previous + std::string("\"");
        }
    };
    struct Repeat : public StringModifier {
        int rep = 1;
        Repeat(int n) : rep(n) {}
        ValueType pass(ValueType previous) const override {
            int m = this->rep;
            std::string ans;
            ans.reserve(m * previous.size());
            while (m--) 
                for (auto& x : previous)
                    ans.push_back(x);
            return ans;
        }
    };

    return Spec("Modifier")
    .addTest(Test::returnsValue<std::string>(
        []() -> std::string {
            std::unique_ptr<StringModifier> mod = std::make_unique<Quote>();
            return mod->pass("hello");
        },
        [](std::string value) { return value == "\"hello\""; },
        "Modifier::pass should apply the function to value"
    ))
    .addTest(Test::returnsValue<std::string>(
        []() -> std::string {
            std::unique_ptr<StringModifier> mod = std::make_unique<Repeat>(3);
            return mod->pass("hello");
        },
        [](std::string value) {
            return value == std::string("hellohellohello");
        },
        "Modifier::pass can take a constructor parameter"
    ));
}

nitron::Spec testPipeline() {
    using namespace nitron;
    using IntModifier = Modifier<int>;

    struct Add10 : public IntModifier {
        ValueType pass(ValueType previous) const override { return previous + 10; }
    };
    struct Mult2 : public IntModifier {
        ValueType pass(ValueType previous) const override { return previous * 2; }
    };

    return Spec("Pipeline")
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Pipeline<int> temp(100);
            return temp.getValue();
        },
        [](int x) { return x == 100; },
        "Baseline: Empty pipeline returns initial value"
    ))
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Pipeline<int> temp(5);
            temp.addModifier(std::make_unique<Add10>());
            temp.addModifier(std::make_unique<Mult2>());
            return temp.getValue();
        },
        [](int x) { return x == 30; },
        "Pipeline Execution: Modifiers calculate sequentially"
    ))
    .addTest(Test::returnsValue<int>(
        []() -> int {
            Pipeline<int> temp(10);
            auto it = temp.addModifier(std::make_unique<Add10>());  
            temp.addModifier(std::make_unique<Mult2>());
            temp.removeModifier(it);
            return temp.getValue();
        },
        [](int x) { return x == 20; },
        "Lifecycle: Removing a modifier correctly updates the pipeline output"
    ));
}

nitron::Spec testProperty() {
    using namespace nitron;
    using IntProp = Property<int>;
    using IntStat = Stat<int>;
    using IntMod  = Modifier<IntStat>;

    struct Decrease : public IntMod {
        int value = 0;
        Decrease(int n) : value(std::max(0, n)) {}
        ValueType pass(ValueType previous) const override {
            previous.current = std::max(0, previous.current - value);
            return previous;
        }
    };
    struct HalfOrigin : public IntMod {
        ValueType pass(ValueType previous) const override {
            int sub = previous.original / 2;
            previous.original -= sub;
            previous.current -= sub;
            return previous;
        }
    };

    return Spec("Property")
    .addTest(Test::returnsValue<IntStat>(
        []() -> IntStat {
            IntProp property (1500);
            property.addModifier(std::make_unique<Decrease>(300));
            return property.getValue();
        },
        [](IntStat stat) { return stat == IntStat(1500, 1500, 1200); },
        "Property carries out operations on value category"
    ))
    .addTest(Test::returnsValue<IntStat>(
        []() -> IntStat {
            IntProp property (3000);
            property.addModifier(std::make_unique<HalfOrigin>());
            property.addModifier(std::make_unique<Decrease>(300));
            return property.getValue();
        },
        [](IntStat stat) { return stat == IntStat(3000, 1500, 1200); },
        "Property operations on origin work"
    ))
    .addTest(Test::returnsValue<int>(
        []() -> int {
            IntProp property (3000);
            property.addModifier(std::make_unique<Decrease>(500));
            property.addModifier(std::make_unique<HalfOrigin>());
            return property.getValue().current;
        },
        [](int value) { return value == 1000; },
        "Property current value can be accessed easily"
    ));
}

} // namespace yugioh::test
