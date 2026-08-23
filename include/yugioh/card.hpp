#pragma once
#include <string>

namespace yugioh
{

class Card {
protected:
    std::string _name;
    std::string _imageURL;
    
public:    
    Card(std::string name, std::string imageURL); // temporarily public
    Card(Card&&)                 = default;
    Card(const Card&)            = default;

    virtual ~Card() = default;

    Card& operator=(Card&&)      = default;
    Card& operator=(const Card&) = default;

    const std::string& name() const;
    const std::string& imageURL() const;
};

} // namespace yugioh
