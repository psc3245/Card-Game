#pragma once
#include "Scene.cpp"
#include "RideTheBus.cpp"
#include "CardShape.cpp"
#include <map>

class RideTheBusScene : public Scene
{
public:
    explicit RideTheBusScene(sf::RenderWindow& window, sf::Font& f)
    : window(window), font(f), header(f, "Welcome to ride the bus", 30), game(1)
    {
        header.setFillColor(sf::Color::Black);
        header.setPosition({350.f, 20.f});

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

        Card *hand = game.getHand(1);

        for (int i = 0; i < 4; i++)
        {
            cards.push_back(CardShape({100.f, 140.f}, {285.f + (110.f * i), 570.f}, hand[i], font));
            cards[i].setTexture(&back_of_card);
        }
    }

    void handleEvent(const sf::Event &event) override
    {
        if (event.is<sf::Event::Closed>())
            window.close();
        if (event.is<sf::Event::MouseMoved>())
        {
            auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            for (int i = 0; i < 4; i++)
            {
                int quad = cards[i].getQuadrant(mousePos);

                if (i == 0 && game.stage == 0)
                {
                    if (quad == -1)
                        cards[i].unhighlight();
                    else if (quad < 2)
                        cards[i].highlight_top(sf::Color::Red, "Red");
                    else
                        cards[i].highlight_bottom(sf::Color::Black, "Black");
                }
                else if (i == 1 && game.stage == 1)
                {
                    if (quad == -1)
                        cards[i].unhighlight();
                    else if (quad < 2)
                        cards[i].highlight_top(sf::Color::Red, "Higher");
                    else
                        cards[i].highlight_bottom(sf::Color::Black, "Lower");
                }
                else if (i == 2 && game.stage == 2)
                {
                    if (quad == -1)
                        cards[i].unhighlight();
                    else if (quad < 2)
                        cards[i].highlight_top(sf::Color::Red, "Outside");
                    else
                        cards[i].highlight_bottom(sf::Color::Black, "Inside");
                }
                else if (i == 3 && game.stage == 3)
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
        if (event.is<sf::Event::MouseButtonPressed>())
        {
            auto mousePos = sf::Mouse::getPosition(window);
            for (int i = 0; i < 4; i++)
            {
                if (i == game.stage)
                {
                    round_outcome result;
                    if (game.stage == 0)
                    {
                        if (cards[i].getQuadrant((sf::Vector2f)mousePos) == 0 || cards[i].getQuadrant((sf::Vector2f)mousePos) == 1)
                        {
                            result = game.handle_round_1('r', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                        }
                        else if (cards[i].getQuadrant((sf::Vector2f)mousePos) == 2 || cards[i].getQuadrant((sf::Vector2f)mousePos) == 3)
                        {
                            result = game.handle_round_1('d', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                        }
                    }
                    else if (game.stage == 1)
                    {
                        if (cards[i].getQuadrant((sf::Vector2f)mousePos) == 0 || cards[i].getQuadrant((sf::Vector2f)mousePos) == 1)
                        {
                            result = game.handle_round_2('h', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                        }
                        else if (cards[i].getQuadrant((sf::Vector2f)mousePos) == 2 || cards[i].getQuadrant((sf::Vector2f)mousePos) == 3)
                        {
                            result = game.handle_round_2('l', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                        }
                    }
                    else if (game.stage == 2)
                    {
                        if (cards[i].getQuadrant((sf::Vector2f)mousePos) == 0 || cards[i].getQuadrant((sf::Vector2f)mousePos) == 1)
                        {
                            result = game.handle_round_3('o', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                        }
                        else if (cards[i].getQuadrant((sf::Vector2f)mousePos) == 2 || cards[i].getQuadrant((sf::Vector2f)mousePos) == 3)
                        {
                            result = game.handle_round_3('i', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                        }
                    }
                    else
                    {
                        int quad = cards[i].getQuadrant((sf::Vector2f)mousePos);
                        switch (quad)
                        {
                        case 0:
                            result = game.handle_round_4('h', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                            break;
                        case 1:
                            result = game.handle_round_4('s', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                            break;
                        case 2:
                            result = game.handle_round_4('c', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                            break;
                        case 3:
                            result = game.handle_round_4('d', 0);
                            cards[i].setTexture(&(*all_cards)[cards[i].getCard().getCardVal()]);
                            cards[i].unhighlight();
                            cards[i].getCard().toggleFaceUp(true);
                            break;
                        }
                    }
                }
            }
        }
    }

    void update()
    {
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(header);
        for (int i = 0; i < cards.size(); i++) {
            window.draw(cards[i]);
        }
    }

private:
RideTheBus game;

    sf::RenderWindow& window;
    sf::Text header;
    sf::Font& font;
    sf::Texture back_of_card;

    std::map<std::string, sf::Texture> *all_cards;

    std::vector<CardShape> cards;

};