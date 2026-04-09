#pragma once
#include "Scene.cpp"
#include "RideTheBus.cpp"
#include "CardShape.cpp"
#include <map>

class RideTheBusScene : public Scene
{
public:
    explicit RideTheBusScene(sf::RenderWindow &window, sf::Font &f, int numPlayers)
        : window(window), font(f),
          header(f, "Welcome to ride the bus", 30), instructions(f, "", 20), goButtonLabel(f, "GO", 50),
          resultLabel(f, "", 30), turn_label(f, "", 30),
          game(numPlayers)
    {
        // Set Up Text Boxes
        header.setStyle(sf::Text::Bold);
        header.setFillColor(sf::Color::Black);
        sf::FloatRect b = header.getLocalBounds();
        header.setOrigin({b.position.x + b.size.x / 2, b.position.y + b.size.y / 2});
        header.setPosition({500.f, 30.f});

        instructions.setStyle(sf::Text::Bold);
        instructions.setFillColor(sf::Color::Black);
        std::string instructions_text = R"(Ride the Bus is a card game where you make a guess about the card each round.
You may give or receieve drinks based on if you are correct or not. 
Be careful, if the choice is impossible, it's double drinks for you.
Ready to play?)";
        instructions.setString(instructions_text);
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
        resultLabel.setPosition({500.f, 300.f});

        turn_label.setStyle(sf::Text::Bold);
        turn_label.setFillColor(sf::Color::Black);
        turn_label.setString("Player 1's Turn:");
        b = turn_label.getLocalBounds();
        turn_label.setOrigin({b.position.x + b.size.x / 2, b.position.y + b.size.y / 2});
        turn_label.setPosition({500.f, 480.f});

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

        // Get the first player's hand
        Card *hand = game.getHand(0);

        for (int i = 0; i < 4; i++)
        {
            current_hand.push_back(CardShape({100.f, 140.f}, {285.f + (110.f * i), 570.f}, hand[i], font));
            current_hand[i].setTexture(&back_of_card);
        }

        round_results = std::vector<std::vector<round_outcome>>(numPlayers, std::vector<round_outcome>(4));
    }

    SceneType handleEvent(const sf::Event &event) override
    {
        if (event.is<sf::Event::Closed>())
            window.close();
        if (event.is<sf::Event::MouseMoved>())
        {
            auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            if (goButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
            {
                goButton.setFillColor(sf::Color(249, 223, 157));
            }
            else
            {
                goButton.setFillColor(sf::Color::Red);
            }
            for (int i = 0; i < 4; i++)
            {
                int quad = current_hand[i].getQuadrant(mousePos);

                if (i == 0 && stage == 0)
                {
                    if (quad == -1)
                        current_hand[i].unhighlight();
                    else if (quad < 2)
                        current_hand[i].highlight_top(sf::Color::Red, "Red");
                    else
                        current_hand[i].highlight_bottom(sf::Color::Black, "Black");
                }
                else if (i == 1 && stage == 1)
                {
                    if (quad == -1)
                        current_hand[i].unhighlight();
                    else if (quad < 2)
                        current_hand[i].highlight_top(sf::Color::Red, "Higher");
                    else
                        current_hand[i].highlight_bottom(sf::Color::Black, "Lower");
                }
                else if (i == 2 && stage == 2)
                {
                    if (quad == -1)
                        current_hand[i].unhighlight();
                    else if (quad < 2)
                        current_hand[i].highlight_top(sf::Color::Red, "Outside");
                    else
                        current_hand[i].highlight_bottom(sf::Color::Black, "Inside");
                }
                else if (i == 3 && stage == 3)
                {
                    if (quad == -1)
                        current_hand[i].unhighlight();
                    else if (quad == 0)
                        current_hand[i].highlight_quadrant(sf::Color::Red, quad, "H");
                    else if (quad == 1)
                        current_hand[i].highlight_quadrant(sf::Color::Black, quad, "S");
                    else if (quad == 2)
                        current_hand[i].highlight_quadrant(sf::Color::Black, quad, "C");
                    else
                        current_hand[i].highlight_quadrant(sf::Color::Red, quad, "D");
                }
            }
        }
        if (event.is<sf::Event::MouseButtonPressed>())
        {
            auto mousePos = sf::Mouse::getPosition(window);
            if (stage == -1)
            {
                if (goButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
                {
                    stage++;
                    instructions.setPosition({500.f, 300.f});
                    instructions.setString(stage_1_instructions);
                }
                return SceneType::NONE;
            }
            for (int i = 0; i < 4; i++)
            {
                if (i == stage)
                {
                    round_outcome result;
                    if (stage == 0)
                    {
                        if (current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 0 ||
                            current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 1)
                        {
                            result = game.handle_round_1('r', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                        }
                        else if (current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 2 ||
                                 current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 3)
                        {
                            result = game.handle_round_1('d', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                        }
                        round_results[turn][0] = result;
                        if (result == CORRECT)
                        {
                            resultLabel.setString("Correct!");
                        }
                        else if (result == WRONG)
                        {
                            resultLabel.setString("WRONG! Take a drink!");
                        }
                        resultLabel.setFillColor(sf::Color::Black);
                        turn++;
                        if (turn == game.getNumPlayers())
                        {
                            stage++;
                            turn = 0;
                            instructions.setString(stage_2_instructions);
                        }
                        return SceneType::NONE;
                    }
                    else if (stage == 1)
                    {
                        if (current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 0 ||
                            current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 1)
                        {
                            result = game.handle_round_2('h', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                        }
                        else if (current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 2 ||
                                 current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 3)
                        {
                            result = game.handle_round_2('l', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                        }
                        round_results[turn][1] = result;
                        if (result == CORRECT)
                        {
                            resultLabel.setString("Correct!");
                        }
                        else if (result == WRONG)
                        {
                            resultLabel.setString("WRONG! Take a drink!");
                        }
                        else
                        {
                            resultLabel.setString("Double drinks! Yikes!");
                        }
                        resultLabel.setFillColor(sf::Color::Black);
                        turn++;
                        if (turn == game.getNumPlayers())
                        {
                            stage++;
                            turn = 0;
                            instructions.setString(stage_3_instructions);
                        }
                        return SceneType::NONE;
                    }
                    else if (stage == 2)
                    {
                        if (current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 0 ||
                            current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 1)
                        {
                            result = game.handle_round_3('o', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                        }
                        else if (current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 2 ||
                                 current_hand[i].getQuadrant((sf::Vector2f)mousePos) == 3)
                        {
                            result = game.handle_round_3('i', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                        }
                        round_results[turn][2] = result;
                        if (result == CORRECT)
                        {
                            resultLabel.setString("Correct!");
                        }
                        else if (result == WRONG)
                        {
                            resultLabel.setString("WRONG! Take a drink!");
                        }
                        else
                        {
                            resultLabel.setString("Double drinks! Yikes!");
                        }
                        resultLabel.setFillColor(sf::Color::Black);
                        turn++;
                        if (turn == game.getNumPlayers())
                        {
                            stage++;
                            turn = 0;
                            instructions.setString(stage_4_instructions);
                        }
                        return SceneType::NONE;
                    }
                    else
                    {
                        int quad = current_hand[i].getQuadrant((sf::Vector2f)mousePos);
                        switch (quad)
                        {
                        case 0:
                            result = game.handle_round_4('h', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                            break;
                        case 1:
                            result = game.handle_round_4('s', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                            break;
                        case 2:
                            result = game.handle_round_4('c', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                            break;
                        case 3:
                            result = game.handle_round_4('d', turn);
                            current_hand[i].setTexture(&(*all_cards)[current_hand[i].getCard().getCardVal()]);
                            current_hand[i].unhighlight();
                            current_hand[i].getCard().toggleFaceUp(true);
                            break;
                        }
                        round_results[turn][3] = result;
                        if (result == CORRECT)
                        {
                            resultLabel.setString("Correct!");
                        }
                        else if (result == WRONG)
                        {
                            resultLabel.setString("WRONG! Take a drink!");
                        }
                        resultLabel.setFillColor(sf::Color::Black);
                        turn++;
                        if (turn == game.getNumPlayers())
                        {
                            stage++;
                            turn = 0;
                        }
                        return SceneType::NONE;
                    }
                }
            }
        }
        return SceneType::NONE;
    }

    void update() override
    {
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(header);
        window.draw(instructions);
        if (stage == -1)
        {
            window.draw(goButton);
            window.draw(goButtonLabel);
        }
        window.draw(resultLabel);
        window.draw(turn_label);
        for (int i = 0; i < current_hand.size(); i++)
        {
            window.draw(current_hand[i]);
        }
    }

    void setNumPlayers(int n)
    {
        game.setNumPlayers(n);
    }

private:
    // Game Model
    RideTheBus game;

    // What round the game is in - starts at negative one for pregame instructions
    int stage = -1;
    // Who's turn it currently is within the round
    int turn = 0;

    std::vector<std::vector<round_outcome>> round_results;

    // Necessary objects for display
    sf::RenderWindow &window;
    sf::Font &font;

    // Texture
    sf::Texture back_of_card;
    std::map<std::string, sf::Texture> *all_cards;

    // Objects Displayed on the Screen
    sf::Text header;

    sf::Text instructions;
    sf::RectangleShape goButton;
    sf::Text goButtonLabel;

    sf::Text resultLabel;

    sf::Text turn_label;
    std::vector<CardShape> current_hand;

    // Constants
    const std::string stage_1_instructions = R"(First round - guess if the card is red or black)";
    const std::string stage_2_instructions = R"(Second round - guess if the next card will be higher or lower than the last card)";
    const std::string stage_3_instructions = R"(Third round - guess if the next card will be inbetween or outside the previous two cards)";
    const std::string stage_4_instructions = R"(Fourth round - guess the suit of the final card)";
};