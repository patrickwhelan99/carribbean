#include "custom.h"

int mainMenu(sf::RenderWindow &app, unsigned &threads)
{
	//Setup MainMenu
	sf::View menuView;
	menuView.setSize(1000, 1000);
	menuView.setCenter(0, 0);

	sf::RectangleShape startButton;
	startButton.setSize(sf::Vector2f(500, 200));
    startButton.setPosition(-250, -300);
    startButton.setFillColor(sf::Color(230, 10, 10));

	sf::RectangleShape optionsButton;
	optionsButton.setSize(sf::Vector2f(500, 200));
    optionsButton.setPosition(-250, 0);
    optionsButton.setFillColor(sf::Color(230, 10, 10));

	sf::RectangleShape quitButton;
	quitButton.setSize(sf::Vector2f(500, 200));
    quitButton.setPosition(-250, 300);
    quitButton.setFillColor(sf::Color(230, 10, 10));

	sf::Texture backgroundTexture;
	srand(time(NULL));
	int randNum = rand() % 2 + 0;
	backgroundTexture.loadFromFile(std::string("menu/image_") + std::to_string(randNum) + std::string(".png"));
	sf::RectangleShape backgroundImage;
	backgroundImage.setSize(menuView.getSize());
	backgroundImage.setOrigin(menuView.getSize().x/2, menuView.getSize().y/2);
	backgroundImage.setPosition(menuView.getCenter());
	backgroundImage.setTexture(&backgroundTexture);



	//Render MainMenu & Handle Events
	while(app.isOpen())
	{
		app.clear();
		app.setView(menuView);
		app.draw(backgroundImage);
		app.draw(startButton);
		app.draw(optionsButton);
		app.draw(quitButton);
		app.display();

		sf::Event event;
		while (app.pollEvent(event))
		{
            if(event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                //if LMB Pressed
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
					if(startButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						gameSetup(app, menuView, threads);
					}

					if(optionsButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						worldBrowser(app, menuView);
					}

					if(quitButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						app.close();
					}
				}

			}
        }
	}

	return 0;
}
