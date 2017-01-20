#include "custom.h"

int loadingScreen(loadingScreenParams &loadingParams)
{

    sf::Context context;
    auto app = loadingParams.app;
    auto camera = loadingParams.camera;
    bool finished = *(loadingParams.finished);

    sf::Shader shader;
    if(!shader.isAvailable() || !shader.loadFromFile("fragShader.frag", sf::Shader::Fragment))
    {
        printf("Failed to load shader\n");
        return -1;
    }
    else
        printf("Shader loaded!\n");

    sf::Texture texture;
    texture.loadFromFile("black.png");

    shader.setParameter("texture", texture);
    shader.setParameter("resolution", static_cast<sf::Vector2f>(app->getSize()));

    sf::RectangleShape rect;
    rect.setSize(static_cast<sf::Vector2f>(app->getSize()));
    rect.setPosition(0, 0);
    rect.setTexture(&texture);

    camera.setCenter(rect.getPosition().x + (rect.getGlobalBounds().width/2), rect.getPosition().y + (rect.getGlobalBounds().height/2));
    camera.setSize(static_cast<sf::Vector2f>(app->getSize()));

    std::string percentageChartedStr;
    sf::Font font;
    font.loadFromFile("DroidSans.ttf");
    sf::Text percentageChartedTxt;
    percentageChartedTxt.setFont(font);
    percentageChartedTxt.setCharacterSize(80);
    percentageChartedTxt.setPosition(rect.getPosition().x + (rect.getGlobalBounds().width/2) - 100, rect.getPosition().y + (rect.getGlobalBounds().height/2) - 40);
    percentageChartedTxt.setColor(sf::Color::White);
    percentageChartedTxt.setString(percentageChartedStr);

    float time = 0.0f;
    float random = 0.0f;
    bool isIncreasing = true;

    while (!finished)//app->isOpen())
    {

        finished = *(loadingParams.finished);
        percentageChartedStr = std::to_string(static_cast<int>(ceil(*(loadingParams.percentageCharted)))) + std::string("%");
        percentageChartedTxt.setString(percentageChartedStr);

        sf::Event event;
        while (app->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app->close();
        }

        if(time>=1 && isIncreasing)
            isIncreasing = false;
        else if(time<=0 && !isIncreasing)
        {
            isIncreasing = true;
            random = float(float(rand() % 100 + 0) / float(100));
            shader.setParameter("random", random);
        }

        if(isIncreasing)
            time += 0.00009;
        else
            time -= 0.00009;

        shader.setParameter("time", time);
        app->clear();
        app->setView(camera);
        app->draw(rect, &shader);
        app->draw(percentageChartedTxt);
        app->display();
    }

    return 0;
}
