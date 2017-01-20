#include "custom.h"

bool initiateCombat(sf::RenderWindow &app, sf::View camera, playerClass player, std::vector<AIBoat> AIBoats)
{
    camera.setSize(1000, 1000);
    camera.setCenter(500, 500);
    app.setView(camera);

    sf::Vector2f mapSize(camera.getSize().x, camera.getSize().y);
    printf("%f, %f\n", mapSize.x, mapSize.y);

    if(AIBoats.size() < 1)
        return -1;

    sf::RectangleShape rangeFinder;
    rangeFinder.setSize(sf::Vector2f(10, 10));
    rangeFinder.setFillColor(sf::Color::Red);

    sf::Vector2f scale(.005, .005);

    player.scale(scale);
    player.setPosition(sf::Vector2f(0, 0));
    //player.shipDirection = right;

    int i = 1;
    for(AIBoat &b : AIBoats)
    {
        b.scale(scale);
        b.setPosition(sf::Vector2f(900-i*50, 900-i*50));
        i++;
    }

    while(app.isOpen())
    {
        sf::Event event;
        while(app.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                app.close();

            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::W)
                {
                    player.shipDirection = up;
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    player.shipDirection = right;
                }
                if(event.key.code == sf::Keyboard::S)
                {
                    player.shipDirection = down;
                }
                if(event.key.code == sf::Keyboard::A)
                {
                    player.shipDirection = left;
                }
                if(event.key.code == sf::Keyboard::Q)
                {
                    player.firingRange -= 100;
                }
                if(event.key.code == sf::Keyboard::E)
                {
                    player.firingRange += 100;
                }
            }
        }

        if(player.shipDirection == up && player.getPosition().y > 0)
            player.setPosition(player.getPosition().x, player.getPosition().y - mapSize.y/30000);
        if(player.shipDirection == right && player.getPosition().x < 950)
            player.setPosition(player.getPosition().x + mapSize.x/30000, player.getPosition().y);
        if(player.shipDirection == down && player.getPosition().y < 950)
            player.setPosition(player.getPosition().x, player.getPosition().y + mapSize.y/30000);
        if(player.shipDirection == left && player.getPosition().x > 0)
            player.setPosition(player.getPosition().x - mapSize.x/30000, player.getPosition().y);


        if(player.shipDirection == up)
            rangeFinder.setPosition(player.getPosition().x + player.getLocalBounds().width/2 + player.firingRange*mapSize.x/1000, player.getPosition().y);
        if(player.shipDirection == right)
            rangeFinder.setPosition(player.getPosition().x, player.getPosition().y + player.getLocalBounds().height/2 + player.firingRange*mapSize.y/1000);
        if(player.shipDirection == down)
            rangeFinder.setPosition(player.getPosition().x - player.getLocalBounds().width/2 - player.firingRange*mapSize.x/1000, player.getPosition().y);
        if(player.shipDirection == left)
            rangeFinder.setPosition(player.getPosition().x, player.getPosition().y - player.getLocalBounds().height/2 - player.firingRange*mapSize.y/1000);

        for(AIBoat &b : AIBoats)
            if(rangeFinder.getGlobalBounds().intersects(b.getGlobalBounds()))
            {
                rangeFinder.setFillColor(sf::Color::Yellow);
                break;
            }
            else
            {
                rangeFinder.setFillColor(sf::Color::Red);
            }

        /// Rendering
        app.clear();

        app.draw(player);
        for(auto &b : AIBoats)
            app.draw(b);
        app.draw(rangeFinder);
        app.display();
    }

    return false;
}
