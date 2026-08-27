#include <bits/move.h>

#include <yugioh/property.hpp>

namespace yugioh {

template <typename T>
template <typename... Args>
Pipeline<T>::Pipeline(Args&&... args) : 
    mBaseValue(std::forward<Args>(args)...) 
{}

template <typename T>
typename Pipeline<T>::ValueType Pipeline<T>::getValue() const {
    ValueType result = this->mBaseValue;
    for (const ModifierRef& modifier : this->mModifierPipeline)
        result = modifier->pass(result);
    return result;
}

template <typename T>
Pipeline<T>::Iterator Pipeline<T>::addModifier(
    typename Pipeline<T>::ModifierRef modifier
) {
    this->mModifierPipeline.emplace_back(std::move(modifier));
    return std::prev(this->mModifierPipeline.end());
}

template <typename T>
void Pipeline<T>::removeModifier(
    typename Pipeline<T>::Iterator modifierIterator
) {
    this->mModifierPipeline.erase(modifierIterator);
}

template <typename T>
Stat<T>::Stat(
    typename Stat<T>::ValueType value
) :
    official(std::move(value)),
    original(std::move(value)),
    current(std::move(value))
{}

template <typename T>
Stat<T>::Stat(
    typename Stat<T>::ValueType officialValue,
    typename Stat<T>::ValueType originalValue,
    typename Stat<T>::ValueType currentValue
) :
    official(std::move(officialValue)),
    original(std::move(originalValue)),
    current(std::move(currentValue))
{}

template <typename T>
bool Stat<T>::operator==(const Stat& rhs) const {
    return this->current == rhs.current;
}

template <typename T>
auto Stat<T>::operator<=>(const Stat& rhs) const {
    return this->current <=> rhs.current;
}

} // namespace yugioh
