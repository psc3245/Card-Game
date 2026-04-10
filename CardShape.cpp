#pragma once
#include <SFML/Graphics.hpp>
#include "Card.h"

class CardShape : public sf::Shape
{
public:

    explicit CardShape(sf::Vector2f bounds, sf::Vector2f pos, Card card, sf::Font& f)
        : i_bounds(bounds), i_pos(pos), i_card(card), font(f), label(f, "", 20)
    {
        i_bounds = bounds;
        i_pos = pos;
        i_card = card;
        this->setPosition(i_pos);
        body = sf::RectangleShape(i_bounds);
        body.setPosition(i_pos);
        label = sf::Text(f, "", 20);
        label.setFillColor(sf::Color::Transparent);
        init_quadrants();
        update();
    }

    void init_quadrants()
    {
        sf::Vector2f middle = {getPos().x + getBounds().x / 2, getPos().y + getBounds().y / 2};
        for (int i = 0; i < 4; i++)
        {
            sf::RectangleShape overlay({getBounds().x / 2, getBounds().y / 2});
            quadrants[i] = overlay;
            quadrants[i].setFillColor(sf::Color::Transparent);
        }
        quadrants[0].setPosition(this->getPosition());
        quadrants[1].setPosition({middle.x, this->getPosition().y});
        quadrants[2].setPosition({this->getPosition().x, middle.y});
        quadrants[3].setPosition(middle);
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

    int getQuadrant(sf::Vector2f mousePos)
    {
        if (!getGlobalBounds().contains(mousePos))
        {
            // Not in the card
            return -1;
        }
        // Get middle point
        sf::Vector2f middle = {getPos().x + getBounds().x / 2, getPos().y + getBounds().y / 2};

        // Get quadrant, if the user clicked exactly middle point default to quad 1
        if (mousePos.x <= middle.x && mousePos.y <= middle.y)
        {
            return 0;
        }
        if (mousePos.x > middle.x && mousePos.y < middle.y)
        {
            return 1;
        }
        if (mousePos.x < middle.x && mousePos.y > middle.y)
        {
            return 2;
        }
        if (mousePos.x > middle.x && mousePos.y > middle.y)
        {
            return 3;
        }
        return -1;
    }

    void setBounds(sf::Vector2f bounds)
    {
        i_bounds = bounds;
        this->body.setSize(bounds);
        update();
    }

    void setPos(sf::Vector2f pos)
    {
        i_pos = pos;
        this->setPosition(i_pos);
        init_quadrants();
        this->body.setPosition(pos);
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

    Card getCard()
    {
        return i_card;
    }

    void setTexture(const sf::Texture *texture)
    {
        body.setTexture(texture);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(body, states);
        for (int i = 0; i < 4; i++)
        {
            target.draw(quadrants[i], states);
        }
        target.draw(label, states);
    }

    void highlight_all(sf::Color color)
    {
        unhighlight();
        for (int i = 0; i < 4; i++)
        {
            quadrants[i].setFillColor(color);
        }
    }

    void highlight_top(sf::Color color, std::string text)
    {
        if (!i_card.face_up)
        {
            unhighlight();
            quadrants[0].setFillColor(color);
            quadrants[1].setFillColor(color);
            label.setString(text);
            sf::FloatRect textBounds = label.getLocalBounds();
            label.setOrigin({textBounds.position.x + textBounds.size.x / 2,
                             textBounds.position.y + textBounds.size.y / 2});
            float y_mid = quadrants[0].getPosition().y + quadrants[0].getSize().y / 2;
            label.setPosition({getPos().x + getBounds().x / 2, y_mid});
            label.setFillColor(sf::Color::White);
        }
    }
    void highlight_bottom(sf::Color color, std::string text)
    {
        if (!i_card.face_up)
        {
            unhighlight();
            quadrants[2].setFillColor(color);
            quadrants[3].setFillColor(color);
            sf::FloatRect textBounds = label.getLocalBounds();
            label.setOrigin({textBounds.position.x + textBounds.size.x / 2,
                             textBounds.position.y + textBounds.size.y / 2});
            float y_mid = quadrants[2].getPosition().y + quadrants[2].getSize().y / 2;
            label.setPosition({getPos().x + getBounds().x / 2, y_mid});
            label.setString(text);
            label.setFillColor(sf::Color::White);
        }
    }
    void highlight_quadrant(sf::Color color, int quadrant, std::string text)
    {
        if (!i_card.face_up)
        {
            unhighlight();
            if (quadrant > 3)
            {
                return;
            }
            quadrants[quadrant].setFillColor(color);
            label.setString(text);
            sf::FloatRect textBounds = label.getLocalBounds();
            label.setOrigin({textBounds.position.x + textBounds.size.x / 2,
                             textBounds.position.y + textBounds.size.y / 2});
            float x_mid = quadrants[quadrant].getPosition().x + quadrants[quadrant].getSize().x / 2;
            float y_mid = quadrants[quadrant].getPosition().y + quadrants[quadrant].getSize().y / 2;
            label.setPosition({x_mid, y_mid});
            label.setFillColor(sf::Color::White);
        }
    }

    void unhighlight()
    {
        for (int i = 0; i < 4; i++)
        {
            quadrants[i].setFillColor(sf::Color::Transparent);
        }
        label.setFillColor(sf::Color::Transparent);
    }

private:
    sf::Vector2f i_bounds;
    sf::Vector2f i_pos;
    Card i_card;
    sf::RectangleShape body;
    sf::RectangleShape quadrants[4];
    sf::Text label;
    sf::Font& font;
};