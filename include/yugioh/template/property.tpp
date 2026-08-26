#include <yugioh/property.hpp>

namespace yugioh
{

template <typename T>
template <typename... Args>
Property<T>::Property(Args&&... args) : 
    mBaseValue(std::forward<Args>(args)...) 
{}

template <typename T>
typename Property<T>::ValueType Property<T>::getValue() const {
    ValueType result = mBaseValue;
    for (const auto& modifier : mModifierPipeline) {
        result = modifier->pass(result); 
    }
    return result;
}

} // namespace yugioh
