#include <yugioh/card.hpp>

namespace yugioh
{

Card::Card(std::string name, std::string imageURL) :
    _name(name),
    _imageURL(imageURL)
{}

const std::string& Card::name() const {
    return this->_name;
}

const std::string& Card::imageURL() const {
    return this->_imageURL;
}

} // namespace yugioh
