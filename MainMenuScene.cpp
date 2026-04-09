#pragma once
#include "Scene.cpp"
#include "MainMenuButtonShape.cpp"

class MainMenuScene : public Scene
{
public:
    explicit MainMenuScene(sf::RenderWindow &window, sf::Font &f)
        : window(window), font(f), header(f, "Welcome to Card Game", 30), instructions(f, "Select Your Game", 30)
    {
        header.setFillColor(sf::Color::Black);
        header.setPosition({350.f, 20.f});
        instructions.setFillColor(sf::Color::Black);
        instructions.setPosition({375.f, 200.f});
        buttons.push_back(MainMenuButtonShape({500, 80}, {250, 300}, font, "Ride the Bus"));
    }

    SceneType handleEvent(const sf::Event &event) override
    {
        if (event.is<sf::Event::Closed>())
            window.close();
        if (event.is<sf::Event::MouseMoved>())
        {
            auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            for (int i = 0; i < buttons.size(); i++)
            {
                if (buttons[i].getGlobalBounds().contains(mousePos))
                {
                    buttons[i].show_all_buttons();
                    int which = buttons[i].checkButtonHighlight(mousePos);
                    if (which != -1)
                    {
                        buttons[i].highlight_one(which);
                    }
                    instructions.setString("How many players?");
                }
                else
                {
                    instructions.setString("Select Your Game");
                    buttons[i].hide_all_buttons();
                }
            }
        }
        if (event.is<sf::Event::MouseButtonPressed>())
        {
            auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            for (int i = 0; i < buttons.size(); i++)
            {
                int which = buttons[i].checkButtonHighlight(mousePos);
                if (which != -1)
                {
                    setNumPlayers(which + 1);
                    // need logic to determine which button was pressed but for now we only have one
                    return SceneType::RIDE_THE_BUS;
                }
            }
        }
    }

    void update() override
    {
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(header);
        window.draw(instructions);
        for (int i = 0; i < buttons.size(); i++)
        {
            window.draw(buttons[i]);
        }
    }

    int getNumPlayers()
    {
        return num_players;
    }

    void setNumPlayers(int n)
    {
        num_players = n;
    }

    Games getSelectedGame()
    {
        return game;
    }

    void setSelectedGame(Games g)
    {
        game = g;
    }

private:
    sf::Text header;
    sf::Text instructions;
    sf::RenderWindow &window;
    sf::Font &font;
    std::vector<MainMenuButtonShape> buttons;
    int num_players = 1;
    Games game = Games::NONE;
};