#include <SFML/Graphics.hpp>
#include "RideTheBusScene.cpp"
#include "MainMenuScene.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 750}), "Card Game");

    sf::Font font;
    font.openFromFile("/System/Library/Fonts/Helvetica.ttc");

    Scene *rideTheBusScene = new RideTheBusScene(window, font);
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
                static_cast<RideTheBusScene *>(rideTheBusScene)->setNumPlayers(players);
                currentScene = rideTheBusScene;
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
