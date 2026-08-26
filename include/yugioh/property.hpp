#pragma once

#include <memory>
#include <list>
#include <utility>

namespace yugioh
{

template <typename T>
class Modifier {
public:
    using ValueType = T;
    virtual ValueType pass(ValueType previous) const = 0;
    virtual ~Modifier() = default;

protected:
    Modifier()                           = default;
    Modifier(Modifier&&)                 = default;
    Modifier(const Modifier&)            = default;
    Modifier& operator=(Modifier&&)      = default;
    Modifier& operator=(const Modifier&) = default;
};

template <typename T>
class Property {
public:
    using ValueType = T;
    using Iterator = typename std::list<std::unique_ptr<Modifier<ValueType>>>::const_iterator;

    template <typename... Args>
    Property(Args&&... args);
    
    ValueType getValue() const;
    
    Iterator addModifier(std::unique_ptr<Modifier<ValueType>> modifier) { return Iterator(); }
    void removeModifier(Iterator modifierIterator) { return; }
    
private:
    const ValueType mBaseValue;
    std::list<std::unique_ptr<Modifier<ValueType>>> mModifierPipeline;
};

void test_property();

} // namespace yugioh

#include <yugioh/template/property.tpp>
