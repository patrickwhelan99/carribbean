#include "../include/custom.h"

void cameraInit(sf::View &camera, sf::View &hudView, sf::RenderWindow &app, sf::Font &mainFont, int gridSize)
{
///Setup camera
    camera.setSize(sf::VideoMode::getDesktopMode().width*(gridSize/48)*200, sf::VideoMode::getDesktopMode().height*(gridSize/48)*200);
    camera.setCenter(0, 0);
    app.setView(camera);
///Setup HUD Camera
    hudView.setSize(1000, 1000);
    hudView.setCenter(0, 0);
///Setup Fonts
    mainFont.loadFromFile("fonts/DroidSans.ttf");
}
