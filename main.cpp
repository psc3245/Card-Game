#include <SFML/Graphics.hpp>
#include "RideTheBusScene.cpp"
#include "MainMenuScene.cpp"
#include "RideTheBusAloneScene.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 750}), "Card Game");

    sf::Font font;
    font.openFromFile("/System/Library/Fonts/Helvetica.ttc");

    Scene *mainMenuScene = new MainMenuScene(window, font);
    Scene *currentScene = mainMenuScene;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            SceneType next = currentScene->handleEvent(*event);
            if (next == SceneType::RIDE_THE_BUS)
            {
                int players = static_cast<MainMenuScene *>(currentScene)->getNumPlayers();
                if (players == 1) currentScene = new RideTheBusAloneScene(window, font);
                else currentScene = new RideTheBusScene(window, font, players);
            }
            else if (next == SceneType::MAIN_MENU)
                currentScene = mainMenuScene;
        }
        window.clear(sf::Color::White);
        currentScene->update();
        currentScene->draw(window);
        window.display();
    }
}
