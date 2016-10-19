#include "server.h"
#include "networking.h"

int main(int argc, char* argv[])
{

	std::vector<world> worlds = loadWorlds(); //loads worlds from file
	std::vector<std::unique_ptr<sf::TcpSocket> > sockets;

	for(auto &w : worlds)
		printf("%i, %i, %s, %s\n", w.seed, w.worldSize, w.name.c_str(), w.imageName.c_str());

    sf::SocketSelector selector;

    sf::TcpListener listener;

    //selector.add(listener);

    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        // error...
    }

	while(true)
    {
                std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
                sf::TcpSocket &cl = *(client);
                cl.setBlocking(false);

                listener.setBlocking(false);

                if(listener.accept(cl) == sf::Socket::Done)
                {
                    printf("READY\n");

                    selector.add(cl);
                    sf::TcpSocket *sp = client.get();
                    sockets.push_back(std::move(client));


                    //Send client the max number of pages
                    sf::Packet maxPageNumPacket;
                    maxPageNumPacket << static_cast<int>(worlds.size())/9;
                    sp->send(maxPageNumPacket);
                    maxPageNumPacket.clear();

                    pageUpdate(sp, worlds);
                }

                for(auto &socket : sockets)
                {
                    sf::TcpSocket *sp = socket.get();
                    sf::TcpSocket &so = *(socket);
                    if(selector.wait(sf::seconds(1)))
                    {
                        if(selector.isReady(so))
                        {
                            printf("Socket Ready!\n");
                            pageUpdate(sp, worlds);

                        }
                        //else
                            //printf("Socket NOT Ready!\n");
                    }
                }
    }

    return 0;
}



int pageUpdate(sf::TcpSocket *client, std::vector<world> &worlds)
{


            printf("Connection recieved from %s\n", client->getRemoteAddress().toString().c_str());

          //Recieve clients page number request

            //client->setBlocking(true);
            sf::Packet packet;
            client->receive(packet);
            int32_t pagenum = -1;
            packet >> pagenum;
            if(pagenum < 0)
            {
                printf("pagenum requested:\t%i\t ERROR!\n", pagenum);
                return -1;
            }

            printf("pagenum requested:\t%i\n", pagenum);
            packet.clear();
            //client->setBlocking(false);


            std::vector<world> sendVector;
            int start = (pagenum)*9;
            int goal = start+9;
            if(start < 0)
            {
                start = 0;
                goal = 9;
            }


            if(goal > static_cast<int>(worlds.size()))
                goal = static_cast<int>(worlds.size());

            //printf("start:\t%i\nworlds:\t%i\ngoal:\t%i\n", start, worlds.size(), goal);

            for(start;start<goal;start++)
                sendVector.push_back(worlds.at(start));

            sf::Packet newPacket;
            int32_t a = static_cast<int32_t>(sendVector.size());
            printf("%i\n", a);
            newPacket << a;
            client->send(newPacket);
            newPacket.clear();

            for(auto &w : sendVector)
            {
                sf::Packet packet;
                packet << w;
                client->send(packet);
                packet.clear();
            }


	return 0;
}
