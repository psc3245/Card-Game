#include "RideTheBus.cpp"
#include <SFML/Graphics.hpp>
#include "CardShape.cpp"
#include <map>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 750}), "Card Game");

    sf::Font font;
    font.openFromFile("/System/Library/Fonts/Helvetica.ttc");

    sf::Text header(font, "Welcome to ride the bus", 30);
    header.setFillColor(sf::Color::Black);
    header.setPosition({350.f, 20.f});

    sf::Texture back_of_card;
    back_of_card.loadFromFile("./Assets/card_back.png");

    char suits[4] = {'H', 'D', 'S', 'C'};
    char values[13] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    std::map<std::string, sf::Texture> all_cards;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            sf::Texture texture;
            std::string card_in_string =  std::string (1, suits[i]) + std::string (1, values[j]);
            texture.loadFromFile("Assets/Cards/" + card_in_string + ".png");
            all_cards[card_in_string] = texture;
        }
    }


    RideTheBus game(1);

    int stage = 1;

    Card *hand = game.getHand(1);

    CardShape *cards = new CardShape[4];

    for (int i = 0; i < 4; i++)
    {
        CardShape card({100.f, 140.f}, {0.f, 0.f}, hand[i]);
        card.setPos({285.f + (110.f * i), 570.f});
        cards[i] = card;
        cards[i].setTexture(&back_of_card);
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseMoved>())
            {
                auto mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < 4; i++)
                {
                    if (i < stage)
                    {
                        if (cards[i].getQuadrant(sf::Vector2f(mousePos)) == 0)
                        {
                            // cards[i].setFillColor(sf::Color::Blue);
                        }
                        else if (cards[i].getQuadrant(sf::Vector2f(mousePos)) < 3)
                        {
                            // cards[i].setFillColor(sf::Color::Red);
                        }
                        else
                        {
                            // cards[i].setFillColor(sf::Color::Green);
                        }
                    }
                }
            }
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < 4; i++)
                {
                    if (i < stage)
                    {
                        if (cards[i].getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                            cards[i].setTexture(&all_cards[cards[i].getCard().getCardVal()]);
                        }
                        if (cards[i].getQuadrant(sf::Vector2f(mousePos)) == 0)
                        {
                            // cards[i].setFillColor(sf::Color::Blue);
                        }
                        else if (cards[i].getQuadrant(sf::Vector2f(mousePos)) < 3)
                        {
                            // cards[i].setFillColor(sf::Color::Red);
                            stage++;
                        }
                        else
                        {
                            // cards[i].setFillColor(sf::Color::Green);
                            stage++;
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(header);
        for (int i = 0; i < 4; i++)
        {
            window.draw(cards[i]);
        }
        window.display();
    }
}