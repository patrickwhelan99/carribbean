#include "../include/custom.h"

int gameSetup(sf::RenderWindow &app, sf::View &menuView, unsigned &threads)
{
	sf::RectangleShape playerNameInputBox;
	playerNameInputBox.setSize(sf::Vector2f(200, 50));
    playerNameInputBox.setPosition(-100, -250);
    playerNameInputBox.setFillColor(sf::Color(255, 10, 10));

	sf::RectangleShape gridSizeInputBox;
	gridSizeInputBox.setSize(sf::Vector2f(100, 50));
    gridSizeInputBox.setPosition(-50, -100);
    gridSizeInputBox.setFillColor(sf::Color(255, 10, 10));

	sf::RectangleShape seedInputBox;
	seedInputBox.setSize(sf::Vector2f(300, 50));
    seedInputBox.setPosition(-150, 0);
    seedInputBox.setFillColor(sf::Color(255, 10, 10));

	sf::RectangleShape startButton;
	startButton.setSize(sf::Vector2f(300, 50));
    startButton.setPosition(-150, 300);
    startButton.setFillColor(sf::Color(255, 10, 10));

	int gridSize = 0;
	uint32_t seed = time(NULL);
	std::string playerName = "PLAYERNAME";

	bool playerNameInputBoxActive = false;
	bool gridSizeInputBoxActive = false;
	bool seedInputBoxActive = false;

	std::string gridSizeStr = "50";
	std::string seedStr = std::to_string(time(NULL));

	sf::Font menuFont;
	menuFont.loadFromFile("fonts/DroidSans.ttf");

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("textures/fish.png");
	sf::RectangleShape backgroundImage;
	backgroundImage.setSize(sf::Vector2f(1000, 1000));
	backgroundImage.setTexture(&backgroundTexture);

	sf::Text playerNameText;
	playerNameText.setFont(menuFont);
	playerNameText.setCharacterSize(25);
	playerNameText.setStyle(sf::Text::Bold);
	playerNameText.setColor(sf::Color::White);
	playerNameText.setPosition(playerNameInputBox.getPosition());

	sf::Text gridSizeText;
	gridSizeText.setFont(menuFont);
	gridSizeText.setCharacterSize(25);
	gridSizeText.setStyle(sf::Text::Bold);
	gridSizeText.setColor(sf::Color::White);
	gridSizeText.setPosition(gridSizeInputBox.getPosition());

	sf::Text seedText;
	seedText.setFont(menuFont);
	seedText.setCharacterSize(25);
	seedText.setStyle(sf::Text::Bold);
	seedText.setColor(sf::Color::White);
	seedText.setPosition(seedInputBox.getPosition());

	//Render MainMenu & Handle Events

    app.setKeyRepeatEnabled(false);

	while(app.isOpen())
	{
		app.clear();
		app.setView(menuView);
		app.draw(backgroundImage);
		app.draw(playerNameInputBox);
		app.draw(gridSizeInputBox);
		app.draw(seedInputBox);
		app.draw(startButton);
		app.draw(playerNameText);
		app.draw(gridSizeText);
		app.draw(seedText);
		app.display();

		sf::Event event;
		while (app.pollEvent(event))
		{
            if(event.type == sf::Event::Closed)
                app.close();

            if(event.type == sf::Event::MouseButtonPressed)
            {

                //if LMB Pressed
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
					if(playerNameInputBox.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						playerNameInputBoxActive = true;
						gridSizeInputBoxActive = false;
						seedInputBoxActive = false;
					}

					else if(gridSizeInputBox.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						gridSizeInputBoxActive = true;
						playerNameInputBoxActive = false;
						seedInputBoxActive = false;
					}

					else if(seedInputBox.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						seedInputBoxActive = true;
						playerNameInputBoxActive = false;
						gridSizeInputBoxActive = false;
					}

					else if(startButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
					{
						if(!seedStr.empty() && seedStr != "")
							seed = std::stoi(seedStr.c_str());
						else
							seed = time(NULL);

						gridSize = std::atoi(gridSizeStr.c_str());
						if(gridSize > 0 && gridSize < 1000)
                            gameMain(app, gridSize, seed, playerName, threads);
					}

					else
					{
						playerNameInputBoxActive = false;
						gridSizeInputBoxActive = false;
						seedInputBoxActive = false;
					}
				}

			}


            if (event.type == sf::Event::TextEntered && playerNameInputBoxActive)
            {
                if(event.text.unicode == '\b' && playerName.size() > 0)
                {
                    playerName.pop_back();
                }
                else if (playerName.size() < 63 && event.text.unicode != '\b')
                {
                    playerName += static_cast<char>(event.text.unicode);

                }
            }

            if (event.type == sf::Event::TextEntered && gridSizeInputBoxActive)
            {
                if(event.text.unicode == '\b' && gridSizeStr.size() > 0)
                {
                    gridSizeStr.pop_back();
                }
                else if(gridSizeStr.size() < 3) // Limit gridsize to 1000 (999 will later be rounded to 1000)
                {
                    gridSizeStr += static_cast<char>(event.text.unicode);
                }
            }

            if (event.type == sf::Event::TextEntered && seedInputBoxActive)
            {
                if(event.text.unicode == '\b' && seedStr.size() > 0)
                {
                    seedStr.pop_back();
                }
                else
                {
                    seedStr += static_cast<char>(event.text.unicode);
                }
            }

            playerNameText.setString(playerName);
            gridSizeText.setString(gridSizeStr);
            seedText.setString(seedStr);
        }

    }
	return 0;
}
