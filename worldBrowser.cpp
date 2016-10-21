#include "custom.h"

int worldBrowser(sf::RenderWindow &app, sf::View &menuView)
{
    sf::Font mainFont;
    mainFont.loadFromFile("DroidSans.ttf");
    std::vector<world> worlds;
    std::vector<sf::Image> images;
    std::vector<textureClass> textures;

    std::vector<worldMenuEntry> menuTiles;
    for(int x=0;x<3;x++)
    {
        for(int y=0;y<3;y++)
        {
            sf::Vector2f v = sf::Vector2f(x*300, y*300);
            worldMenuEntry newEntry(v, mainFont);
            menuTiles.push_back(newEntry);
        }
    }

    sf::RectangleShape prevButton;
    prevButton.setSize(sf::Vector2f(50, 50));
    prevButton.setPosition(menuTiles.at(1).image.getPosition() + sf::Vector2f(-75, menuTiles.at(1).image.getLocalBounds().height/2));
    prevButton.setFillColor(sf::Color::Red);

    sf::RectangleShape nextButton;
    nextButton.setSize(sf::Vector2f(50, 50));
    nextButton.setPosition(menuTiles.at(7).image.getPosition() + sf::Vector2f(menuTiles.at(7).image.getLocalBounds().width + 25, menuTiles.at(7).image.getLocalBounds().height/2));
    nextButton.setFillColor(sf::Color::Red);



    menuView.setCenter(sf::Vector2f(425, 450));


    /// Setup initial TCP connection
	sf::TcpSocket socket;
	socket.setBlocking(true);
	sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
	if (status != sf::Socket::Done)
	{
	   std::cerr << "COULDN'T ESABLISH CONNECTION!\n";
	}
	else
	{
		printf("Connected to %s:%u!\n", socket.getRemoteAddress().toString().c_str(), socket.getRemotePort());
		int pageNum = 0;
		int maxPageNum = 0;

		sf::Packet maxPageNumPacket;
        socket.receive(maxPageNumPacket);
        maxPageNumPacket >> maxPageNum;
        printf("MaxPageNum:\t%i\n", maxPageNum);
        int i = 0;

		while(app.isOpen())
		{
			bool newPage = false;
			if(i == 0) // Update first time without button press
                newPage = true;

            i++;

			sf::Event event;
			while (app.pollEvent(event))
			{
                if (event.type == sf::Event::Closed)
                    app.close();

                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if(prevButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        pageNum -= 1;
                        newPage = true;
                    }

                    if(nextButton.getGlobalBounds().contains(app.mapPixelToCoords(sf::Mouse::getPosition())))
                    {
                        pageNum += 1;
                        newPage = true;
                    }
                }
            }

            if(pageNum < 0)
                pageNum = maxPageNum;
            if(pageNum > maxPageNum)
                pageNum = 0;


            if(newPage)
            {

            /// Request page number from server and recieve number of worlds to draw
			sf::Packet packet;
			packet << pageNum;
			socket.send(packet);
			sf::Packet newPacket;
			socket.receive(newPacket);
			int32_t toRecieve;
			newPacket >> toRecieve;
			printf("Worlds to recieve:\t%i\n", toRecieve);


			sf::Ftp ftp;
            sf::Ftp::Response response = ftp.connect(socket.getRemoteAddress());
            std::cout << response.getMessage() << std::endl;
            response  = ftp.login("anonymous", "anonymous@carribbean.me");
            std::cout << response.getMessage() << std::endl;



            if(response.getStatus() == sf::Ftp::Response::LoggedIn)
            {
                printf("Okay!\n");
                response = ftp.changeDirectory("carribbean/images");
                std::cout << response.getMessage() << std::endl;
                images.empty();
                textures.empty();

                for(auto &m : menuTiles)
                {
                    m.image.setTexture(nullptr);
                    m.nameStr = "";
                }

                for(int i=0; i<toRecieve; i++)
                {
                    sf::Packet neuPacket;
                    socket.receive(neuPacket);
                    world neuWelt;
                    neuPacket >> neuWelt;
                    worlds.push_back(neuWelt);


                    menuTiles.at(i).nameStr = worlds.at(i).name;


                    response = ftp.download(neuWelt.imageName, "/home/paz/Downloads/carribbean", sf::Ftp::Binary);
                    std::cout << response.getMessage() << std::endl;
/*
                    sf::Image newImage;
                    newImage.loadFromFile(neuWelt.imageName);
                    images.push_back(newImage);
*/
                    textureClass newTexture;
                    newTexture.loadFromFile(neuWelt.imageName);
                    newTexture.name == neuWelt.imageName;
                    textures.push_back(newTexture);

                }

                for(int i=0;i<toRecieve;i++)
                    menuTiles.at(i).image.setTexture(&textures.at(i));

            }
            }

            app.clear();
            app.setView(menuView);
            for(auto &t : menuTiles)
            {
                t.nameText.setString(t.nameStr);
                app.draw(t.tile);
                app.draw(t.image);
                app.draw(t.nameText);
            }
            app.draw(prevButton);
            app.draw(nextButton);

            app.display();

		}


	}

	return 0;
}
