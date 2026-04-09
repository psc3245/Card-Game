#pragma once
#include <SFML/Graphics.hpp>

class MainMenuButtonShape : public sf::Shape
{
public:
    explicit MainMenuButtonShape(sf::Vector2f bounds, sf::Vector2f pos, sf::Font &f, std::string text)
        : i_bounds(bounds), i_pos(pos), font(f), label(f, text, 50)
    {
        i_bounds = bounds;
        i_pos = pos;
        this->setPosition(i_pos);
        body = sf::RectangleShape(i_bounds);
        body.setPosition(i_pos);
        body.setFillColor(button_color);
        body.setOutlineColor(sf::Color::Black);
        body.setOutlineThickness(2);
        label = sf::Text(f, text, 50);
        label.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = label.getLocalBounds();
        label.setOrigin({textBounds.position.x + textBounds.size.x / 2,
                         textBounds.position.y + textBounds.size.y / 2});
        label.setPosition({i_pos.x + i_bounds.x / 2, i_pos.y + i_bounds.y / 2});
        init_buttons();
        update();
    }

    void init_buttons()
    {
        float subWidth = (i_bounds.x - (padding * 5)) / 4;
        float subHeight = i_bounds.y - (padding * 2);
        for (int i = 0; i < 4; i++)
        {
            float subX = i_pos.x + padding + (i * (subWidth + padding));
            float subY = i_pos.y + padding;
            sf::RectangleShape button({subWidth, subHeight});
            playerButtons[i] = button;
            playerButtons[i].setPosition({subX, subY});
            playerButtons[i].setFillColor(sf::Color::Transparent);
            playerButtonLabels.push_back(sf::Text(font, std::to_string(i + 1), 50));
            playerButtonLabels[i].setFillColor(sf::Color::Transparent);
            playerButtonLabels[i].setString(std::to_string(i + 1));
            sf::FloatRect textBounds = playerButtonLabels[i].getLocalBounds();
            playerButtonLabels[i].setOrigin({textBounds.position.x + textBounds.size.x / 2,
                                             textBounds.position.y + textBounds.size.y / 2});
            playerButtonLabels[i].setPosition({subX + subWidth / 2, subY + subHeight / 2});
        }
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

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(body, states);
        for (int i = 0; i < 4; i++)
        {
            target.draw(playerButtons[i], states);
            target.draw(playerButtonLabels[i], states);
        }
        target.draw(label, states);
    }

    void show_all_buttons()
    {
        label.setFillColor(sf::Color::Transparent);
        for (int i = 0; i < 4; i++)
        {
            playerButtons[i].setFillColor(highlight_all_color);
            playerButtonLabels[i].setFillColor(sf::Color::Black);
        }
    }
    void hide_all_buttons()
    {
        for (int i = 0; i < 4; i++)
        {
            playerButtons[i].setFillColor(sf::Color::Transparent);
            playerButtonLabels[i].setFillColor(sf::Color::Transparent);
        }
        label.setFillColor(sf::Color::Black);
    }

    void highlight_one(int which)
    {
        show_all_buttons();
        playerButtons[which].setFillColor(highlight_one_color);
    }

    int checkButtonHighlight(sf::Vector2f mousePos)
    {
        if (!body.getGlobalBounds().contains(mousePos))
            return -1;
        for (int i = 0; i < 4; i++)
        {
            if (playerButtons[i].getGlobalBounds().contains(mousePos))
                return i;
        }
        return -1;
    }

private:
    sf::Vector2f i_bounds;
    sf::Vector2f i_pos;
    sf::RectangleShape body;
    sf::RectangleShape playerButtons[4];
    std::vector<sf::Text> playerButtonLabels;
    sf::Text label;
    sf::Font &font;
    const float padding = 10.0;
    const sf::Color button_color = sf::Color::Red;
    const sf::Color highlight_all_color = sf::Color::White;
    const sf::Color highlight_one_color = sf::Color(249, 223, 157);
};