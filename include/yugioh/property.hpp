#pragma once

#include <nitron/spec.hpp>

#include <memory>
#include <list>
#include <utility>

namespace yugioh {

template <typename T>
struct Modifier {
    using ValueType = T;

    Modifier()                           = default;
    Modifier(Modifier&&)                 = default;
    Modifier(const Modifier&)            = default;
    virtual ~Modifier()                  = default;
    Modifier& operator=(Modifier&&)      = default;
    Modifier& operator=(const Modifier&) = default;

    virtual ValueType pass(ValueType previous) const = 0;
};

template <typename T>
class Pipeline {
public:
    using ValueType   = T;
    using ModifierRef = std::unique_ptr<Modifier<ValueType>>;
    using Iterator    = std::list<ModifierRef>::const_iterator;
    
    Pipeline(Pipeline&&)                 = default;
    Pipeline(const Pipeline&)            = default;
    ~Pipeline()                          = default;
    Pipeline& operator=(Pipeline&&)      = default;
    Pipeline& operator=(const Pipeline&) = default;

    template <typename... Args>
    Pipeline(Args&&... args);
    
    ValueType getValue() const;

    Iterator addModifier(ModifierRef modifier);
    void removeModifier(Iterator modifierIterator);

private:
    const ValueType mBaseValue {};
    std::list<ModifierRef> mModifierPipeline {};
};

template <typename T>
struct Stat {
    using ValueType = T;

    Stat(Stat&&)                 = default;
    Stat(const Stat&)            = default;
    ~Stat()                      = default;
    Stat& operator=(Stat&&)      = default;
    Stat& operator=(const Stat&) = default;

    Stat(ValueType value);
    Stat(ValueType officialValue, ValueType originalValue, ValueType currentValue);

    bool operator==(const Stat& rhs) const;
    auto operator<=>(const Stat& rhs) const;

    ValueType official {};
    ValueType original {};
    ValueType current {};
};

template <typename T>
using Property = Pipeline<Stat<T>>;

namespace test {

nitron::Spec testModifier();
nitron::Spec testPipeline();
nitron::Spec testProperty();

} // namespace test

} // namespace yugioh

#include <yugioh/template/property.tpp>
