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

        all_hands = std::vector<std::vector<CardShape>>(numPlayers);

        for (int i = 0; i < numPlayers; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                all_hands[i].push_back(CardShape({100.f, 140.f}, {285.f + (110.f * j), 570.f}, game.getHand(i)[j], font));
                all_hands[i][j].setTexture(&back_of_card);
                all_hands[i][j].set_is_active(false);
            }
        }
    }

    SceneType handleEvent(const sf::Event &event) override
    {
        if (event.is<sf::Event::Closed>())
            window.close();
        if (event.is<sf::Event::MouseMoved>())
        {
            auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            if (!isRoundActive)
            {
                if (goButton.getGlobalBounds().contains((sf::Vector2f)mousePos))
                {
                    goButton.setFillColor(sf::Color(249, 223, 157));
                }
                else
                {
                    goButton.setFillColor(sf::Color::Red);
                }
            }
            if (isRoundActive)
            {
                int quad = all_hands[game.getTurn()][game.getStage()].getQuadrant(mousePos);

                if (game.getStage() == 0)
                {
                    if (quad == -1)
                        all_hands[game.getTurn()][game.getStage()].unhighlight();
                    else if (quad < 2)
                        all_hands[game.getTurn()][game.getStage()].highlight_top(sf::Color::Red, "Red");
                    else
                        all_hands[game.getTurn()][game.getStage()].highlight_bottom(sf::Color::Black, "Black");
                }
                else if (game.getStage() == 1)
                {
                    if (quad == -1)
                        all_hands[game.getTurn()][game.getStage()].unhighlight();
                    else if (quad < 2)
                        all_hands[game.getTurn()][game.getStage()].highlight_top(sf::Color::Red, "Higher");
                    else
                        all_hands[game.getTurn()][game.getStage()].highlight_bottom(sf::Color::Black, "Lower");
                }
                else if (game.getStage() == 2)
                {
                    if (quad == -1)
                        all_hands[game.getTurn()][game.getStage()].unhighlight();
                    else if (quad < 2)
                        all_hands[game.getTurn()][game.getStage()].highlight_top(sf::Color::Red, "Outside");
                    else
                        all_hands[game.getTurn()][game.getStage()].highlight_bottom(sf::Color::Black, "Inside");
                }
                else if (game.getStage() == 3)
                {
                    if (quad == -1)
                        all_hands[game.getTurn()][game.getStage()].unhighlight();
                    else if (quad == 0)
                        all_hands[game.getTurn()][game.getStage()].highlight_quadrant(sf::Color::Red, quad, "H");
                    else if (quad == 1)
                        all_hands[game.getTurn()][game.getStage()].highlight_quadrant(sf::Color::Black, quad, "S");
                    else if (quad == 2)
                        all_hands[game.getTurn()][game.getStage()].highlight_quadrant(sf::Color::Black, quad, "C");
                    else
                        all_hands[game.getTurn()][game.getStage()].highlight_quadrant(sf::Color::Red, quad, "D");
                }
            }
        }
        if (event.is<sf::Event::MouseButtonPressed>())
        {
            auto mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            if (!isRoundActive)
            {
                if (goButton.getGlobalBounds().contains(mousePos))
                {
                    instructions.setPosition({500.f, 300.f});
                    instructions.setString(getInstructionsForRound());
                    isRoundActive = true;
                    all_hands[game.getTurn()][game.getStage()].set_is_active(true);
                }
                return SceneType::NONE;
            }
            int quad = all_hands[game.getTurn()][game.getStage()].getQuadrant(mousePos);
            if (quad == -1)
            {
                return SceneType::NONE;
            }
            int prevTurn = game.getTurn();
            int prevStage = game.getStage();
            if (game.getStage() == 0)
            {
                if (quad == 0 || quad == 2)
                    last_result = game.submitGuess('r');
                else
                    last_result = game.submitGuess('b');
            }
            else if (game.getStage() == 1)
            {
                if (quad == 0 || quad == 2)
                    last_result = game.submitGuess('h');
                else
                    last_result = game.submitGuess('l');
            }
            else if (game.getStage() == 2)
            {
                if (quad == 0 || quad == 2)
                    last_result = game.submitGuess('o');
                else
                    last_result = game.submitGuess('i');
            }
            else if (game.getStage() == 3)
            {
                if (quad == 0)
                    last_result = game.submitGuess('h');
                else if (quad == 1)
                    last_result = game.submitGuess('s');
                else if (quad == 2)
                    last_result = game.submitGuess('c');
                else
                    last_result = game.submitGuess('d');
            }
            isRoundActive = false;
            update(prevTurn, prevStage);
        }
        return SceneType::NONE;
    }

    void update() override
    {
    }

    void update(int prevTurn, int prevStage)
    {
        if (last_result == CORRECT)
        {
            resultLabel.setString("Correct! Give out " + std::to_string((prevStage + 1) * 2) + " drinks!");
        }
        else if (last_result == WRONG)
        {
            resultLabel.setString("WRONG! Take " + std::to_string((prevStage + 1) * 2) + " drinks!");
        }
        else
        {
            resultLabel.setString("Yikes! Double drinks! Take " + std::to_string((prevStage + 1) * 4) + " drinks!");
        }
        resultLabel.setFillColor(sf::Color::Black);

        goButton.setFillColor(sf::Color::Red);
        
        all_hands[prevTurn][prevStage].set_is_active(false);
        all_hands[prevTurn][prevStage].unhighlight();
        all_hands[game.getTurn()][game.getStage()].set_is_active(true);
        all_hands[prevTurn][prevStage].setTexture(&(*all_cards)[all_hands[prevTurn][prevStage].getCard().getCardVal()]);
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(header);
        window.draw(instructions);
        if (!isRoundActive)
        {
            window.draw(goButton);
            window.draw(goButtonLabel);
        }
        window.draw(resultLabel);
        window.draw(turn_label);
        for (int i = 0; i < game.getNumPlayers(); i++)
        {
            for (int j = 0; j < 4; j++)
            {
                window.draw(all_hands[i][j]);
            }
        }
    }

    void setNumPlayers(int n)
    {
        game.setNumPlayers(n);
    }

    std::string getInstructionsForRound()
    {
        switch (game.getStage())
        {
        case 0:
            return stage_1_instructions;
            break;
        case 1:
            return stage_2_instructions;
            break;
        case 2:
            return stage_3_instructions;
            break;
        case 3:
            return stage_4_instructions;
            break;
        }
    }

private:
    // Game Model
    RideTheBus game;

    // Determines whether or not we allow guesses
    bool isRoundActive = false;

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
    std::vector<std::vector<CardShape>> all_hands;

    round_outcome last_result;

    // Constants
    const std::string stage_1_instructions = R"(First round - guess if the card is red or black)";
    const std::string stage_2_instructions = R"(Second round - guess if the next card will be higher or lower than the last card)";
    const std::string stage_3_instructions = R"(Third round - guess if the next card will be inbetween or outside the previous two cards)";
    const std::string stage_4_instructions = R"(Fourth round - guess the suit of the final card)";
};