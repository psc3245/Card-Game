#pragma once
#include "Scene.cpp"
#include "RideTheBusAlone.cpp"

class RideTheBusAloneScene : Scene
{

public:

    explicit RideTheBusAloneScene() : game() {
        
    }
    SceneType handleEvent(const sf::Event &event) {}
    void update() {}
    void draw(sf::RenderWindow &window) {}

private:
    RideTheBusAlone game;
};