#pragma once
#include <SFML/Graphics.hpp>

class Scene {
    public:
        virtual void handleEvent(const sf::Event &event) = 0;
        virtual void update() = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
};