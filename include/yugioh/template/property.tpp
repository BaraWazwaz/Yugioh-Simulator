#include <yugioh/property.hpp>

namespace yugioh {

template <typename T>
template <typename... Args>
Property<T>::Property(Args&&... args) : 
    mBaseValue(std::forward<Args>(args)...) 
{}

template <typename T>
typename Property<T>::ValueType Property<T>::getValue() const {
    ValueType result = this->mBaseValue;
    for (const auto& modifier : this->mModifierPipeline) {
        result = modifier->pass(result); 
    }
    return result;
}

template <typename T>
Property<T>::Iterator Property<T>::addModifier(
    std::unique_ptr<Modifier<T>> modifier
) {
    this->mModifierPipeline.emplace_back(std::move(modifier));
    return std::prev(this->mModifierPipeline.end());
}

template <typename T>
void Property<T>::removeModifier(
    Property<T>::Iterator modifierIterator
) {
    this->mModifierPipeline.erase(modifierIterator);
}

} // namespace yugioh
