#pragma once
#include <SFML/Graphics.hpp>

enum class SceneType {
    NONE,
    MAIN_MENU,
    RIDE_THE_BUS
};

enum class Games {
    NONE,
    RIDE_THE_BUS
};

class Scene {
    public:
        virtual SceneType handleEvent(const sf::Event &event) = 0;
        virtual void update() = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
};