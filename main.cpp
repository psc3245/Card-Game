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
    std::map<std::string, sf::Texture> *all_cards = new std::map<std::string, sf::Texture>();
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

    RideTheBus game(1);

    Card *hand = game.getHand(1);

    std::vector<CardShape> cards;
    for (int i = 0; i < 4; i++)
    {
        cards.push_back(CardShape({100.f, 140.f}, {285.f + (110.f * i), 570.f}, hand[i], font));
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
                auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
                for (int i = 0; i < 4; i++)
                {
                    int quad = cards[i].getQuadrant(mousePos);

                    if (i == 0)
                    {
                        if (quad == -1)
                            cards[i].unhighlight();
                        else if (quad < 2)
                            cards[i].highlight_top(sf::Color::Red, "Red");
                        else
                            cards[i].highlight_bottom(sf::Color::Black, "Black");
                    }
                    else if (i == 1)
                    {
                        if (quad == -1)
                            cards[i].unhighlight();
                        else if (quad < 2)
                            cards[i].highlight_top(sf::Color::Red, "Higher");
                        else
                            cards[i].highlight_bottom(sf::Color::Black, "Lower");
                    }
                    else if (i == 2)
                    {
                        if (quad == -1)
                            cards[i].unhighlight();
                        else if (quad < 2)
                            cards[i].highlight_top(sf::Color::Red, "Outside");
                        else
                            cards[i].highlight_bottom(sf::Color::Black, "Inside");
                    }
                    else
                    {
                        if (quad == -1)
                            cards[i].unhighlight();
                        else if (quad == 0)
                            cards[i].highlight_quadrant(sf::Color::Red, quad, "H");
                        else if (quad == 1)
                            cards[i].highlight_quadrant(sf::Color::Black, quad, "S");
                        else if (quad == 2)
                            cards[i].highlight_quadrant(sf::Color::Black, quad, "C");
                        else
                            cards[i].highlight_quadrant(sf::Color::Red, quad, "D");
                    }
                }
            }
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < 4; i++)
                {
                    if (i < game.stage)
                    {
                        if (cards[i].getGlobalBounds().contains(sf::Vector2f(mousePos)))
                        {
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                        }
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
