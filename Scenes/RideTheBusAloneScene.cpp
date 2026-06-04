#pragma once
#include "Scene.cpp"
#include "RideTheBusAlone.cpp"
#include "CardShape.cpp"
#include <map>
#include "util.cpp"

class RideTheBusAloneScene : public Scene
{

public:
    explicit RideTheBusAloneScene(sf::RenderWindow &window, sf::Font &f)
        : window(window), font(f), game(),
          header(f, "Welcome to ride the bus", 30), instructions(f, "", 20),
          goButtonLabel(f, "GO", 50),
          resultLabel(f, "", 30)
    {

        // Set Up Text Boxes
        header.setStyle(sf::Text::Bold);
        header.setFillColor(sf::Color::Black);
        sf::FloatRect b = header.getLocalBounds();
        header.setOrigin({b.position.x + b.size.x / 2, b.position.y + b.size.y / 2});
        header.setPosition({500.f, 30.f});

        instructions.setStyle(sf::Text::Bold);
        instructions.setFillColor(sf::Color::Black);
        std::string instructions_text = R"(Welcome to the Ride The Bus Gauntlet. The only way out is to get four choices correct in a row. Are you up for the challenge?)";
        instructions.setString(wrapText(instructions_text, 600, instructions));
        b = instructions.getLocalBounds();
        instructions.setOrigin({b.position.x + b.size.x / 2, b.position.y + b.size.y / 2});
        instructions.setPosition({500.f, 150.f});

        goButton.setFillColor(sf::Color::Red);
        goButton.setOutlineColor(sf::Color::Black);
        goButton.setOutlineThickness(2);
        goButton.setSize({300, 80});
        goButton.setPosition({500.f - 150.f, 300.f - 40.f});

        goButtonLabel.setStyle(sf::Text::Bold);
        goButtonLabel.setFillColor(sf::Color::Black);
        b = goButtonLabel.getLocalBounds();
        goButtonLabel.setOrigin({b.position.x + b.size.x / 2, b.position.y + b.size.y / 2});
        goButtonLabel.setPosition({500.f, 300.f});

        resultLabel.setStyle(sf::Text::Bold);
        resultLabel.setFillColor(sf::Color::Transparent);
        b = resultLabel.getLocalBounds();
        resultLabel.setOrigin({b.position.x + b.size.x / 2, b.position.y + b.size.y / 2});
        resultLabel.setPosition({500.f, 480.f});

        // Set Up All Textures
        back_of_card.loadFromFile("./Assets/card_back.png");

        char suits[4] = {'H', 'D', 'S', 'C'};
        char values[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
        all_cards = new std::map<std::string, sf::Texture>();
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                sf::Texture texture;
                std::string card_in_string = std::string(1, suits[i]) + std::string(1, values[j]);
                texture.loadFromFile("Assets/Cards/" + card_in_string + ".png");
                (*all_cards)[card_in_string] = texture;
            }
        }

        RideTheBusAlone game();
    }
    SceneType handleEvent(const sf::Event &event)
    {
        if (event.is<sf::Event::Closed>())
            window.close();
        if (event.is<sf::Event::MouseMoved>())
        {
        }
        if (event.is<sf::Event::MouseMoved>())
        {
        }
    }
    void update() {}
    void draw(sf::RenderWindow &window) {}

private:
    RideTheBusAlone game;

    sf::RenderWindow &window;
    sf::Font &font;

    sf::Texture back_of_card;
    std::map<std::string, sf::Texture> *all_cards;

    sf::Text header;
    sf::Text instructions;

    sf::RectangleShape goButton;
    sf::Text goButtonLabel;

    sf::Text resultLabel;

    std::vector<CardShape> cards;
};