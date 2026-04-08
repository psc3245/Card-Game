#include "RideTheBus.cpp"
#include <SFML/Graphics.hpp>
#include "CardShape.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 750}), "Card Game");

    sf::Font font;
    font.openFromFile("/System/Library/Fonts/Helvetica.ttc");

    sf::Text header(font, "Welcome to ride the bus", 30);
    header.setFillColor(sf::Color::Black);
    header.setPosition({350.f, 20.f});

    CardShape *cards = new CardShape[4];

    for (int i = 0; i < 4; i++)
    {
        Card c;
        CardShape card({100.f, 140.f}, {0.f, 0.f}, sf::Color::Blue, c);
        card.setPos({285.f + (110.f * i), 570.f});
        cards[i] = card;
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                printf("clicked\n");
                auto mousePos = sf::Mouse::getPosition(window);
                for (int i = 0; i < 4; i++)
                {
                    if (cards[i].getQuadrant(sf::Vector2f(mousePos)) != 0) {
                    cout << "Card " << i << "quadrant " <<  cards[i].getQuadrant(sf::Vector2f(mousePos)) << "clicked." << endl;
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