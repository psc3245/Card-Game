#include <SFML/Graphics.hpp>
#include "RideTheBusScene.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 750}), "Card Game");

    sf::Font font;
    font.openFromFile("/System/Library/Fonts/Helvetica.ttc");

    Scene* currentScene = new RideTheBusScene(window, font);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            currentScene->handleEvent(*event);
        }
        currentScene->update();
        currentScene->draw(window);
        window.display();
    }
}
