#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"

class CardShape : public sf::Shape
{
public:
    
    CardShape() : i_bounds({0, 0}), i_pos({0, 0}), 
    i_color(sf::Color::White), i_card(Card()) {}
    
    explicit CardShape(
        sf::Vector2f bounds,
        sf::Vector2f pos,
        sf::Color color,
        Card card)
    {
        i_bounds = bounds;
        i_pos = pos;
        i_color = color;
        i_card = card;
        this->setPosition(i_pos);
    this->setFillColor(i_color);
        update();
    }

    std::size_t getPointCount() const override
    {
        return 4;
    }

    sf::Vector2f getPoint(std::size_t index) const override
    {
        switch (index)
        {
        case 0:
            return {0, 0};
        case 1:
            return {i_bounds.x, 0};
        case 2:
            return {i_bounds.x, i_bounds.y};
        case 3:
            return {0, i_bounds.y};
        }
        return {};
    }

    void setBounds(sf::Vector2f bounds)
    {
        i_bounds = bounds;
        update();
    }

    void setPos(sf::Vector2f pos)
    {
        i_pos = pos;
        this->setPosition(i_pos);
        update();
    }

    void setColor(sf::Color color)
    {
        i_color = color;
        this->setFillColor(i_color);
        update();
    }

    void setCard(Card card)
    {
        i_card = card;
    }

    sf::Vector2f getPos()
    {
        return i_pos;
    }

    sf::Vector2f getBounds()
    {
        return i_bounds;
    }

    sf::Color getColor()
    {
        return i_color;
    }

    Card getCard()
    {
        return i_card;
    }

private:
    sf::Vector2f i_bounds;
    sf::Vector2f i_pos;
    sf::Color i_color;
    Card i_card;
};