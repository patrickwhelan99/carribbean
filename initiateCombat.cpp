#include "custom.h"

bool initiateCombat(sf::RenderWindow &app, sf::View camera, playerClass &player, std::vector<AIBoat> &AIBoats)
{
    camera.setSize(1000, 1000);
    camera.setCenter(500, 500);
    app.setView(camera);

    sf::FloatRect intersectionRect;
    intersectionRect.top = 0;
    intersectionRect.left = 0;
    intersectionRect.height = 1000;
    intersectionRect.width = 1000;
    printf("%f, %f\n", intersectionRect.top, intersectionRect.left);

    sf::Vector2f mapSize(camera.getSize().x, camera.getSize().y);
    //printf("%f, %f\n", mapSize.x, mapSize.y);

    ///setup pathing nodes
    std::vector<sf::RectangleShape> nodes;
    for(int i=0; i<100; i++)
    {
        for(int j=0; j<100; j++)
        {
            sf::RectangleShape node(sf::Vector2f(1, 1));
            node.setPosition(i*10, j*10);
            node.setFillColor(sf::Color::Red);
            nodes.push_back(node);
        }
    }


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

    std::clock_t start = std::clock();

    while(app.isOpen())
    {

        AIBattleLoop(AIBoats, player, nodes, intersectionRect, start);


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
                if(event.key.code == sf::Keyboard::Return)
                {
                    for(AIBoat &b : AIBoats)
                    {
                        if(rangeFinder.getGlobalBounds().intersects(b.getGlobalBounds()))
                            player.fireCannons(true, b);
                        else
                            player.fireCannons(false, b);
                    }
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

        bool allDead = true;
        for(AIBoat &b : AIBoats)
        {
            if(!b.inactive)
                allDead = false;
        }

        if(allDead)
        {
            endBattle(player, AIBoats, true);
            break;
        }
        if(player.health <= 0.0f)
        {
            endBattle(player, AIBoats, false);
        }


        /// Rendering
        app.clear();

        //for(auto &n : nodes)
            //app.draw(n);

        app.draw(player);
        for(auto &b : AIBoats)
            if(!b.inactive)
                app.draw(b);



        app.draw(rangeFinder);
        app.display();
    }

    return false;
}
