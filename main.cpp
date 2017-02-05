#include "custom.h"

int main(int argc, char* argv[])
{
    /// Create the main window
    sf::RenderWindow app(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Carribbean", sf::Style::None);
    /// Gather available threads
    unsigned threads = std::thread::hardware_concurrency();
    if(threads==0){threads=1;} // 0 Returned if # of threads undetectable, in such a case future code is unusable so threads must be set
    printf("\n\n\tFound %u threads\n\n", threads);

	mainMenu(app, threads);

	return 0;
}

int gameMain(sf::RenderWindow &app, int &gridSize, uint32_t &seed, std::string &playerName, unsigned &threads)
{
    if(gridSize % 2 != 0)
        gridSize += 1; // Gridsize must be even for adjacent Tile calculations

    if(gridSize % 2 != 0)
        gridSize += 1; // Gridsize must be even for adjacent Tile calculations


    ///  Setup Cameras
    sf::View camera;
    sf::View hudView;
    sf::Font mainFont;
    cameraInit(camera, hudView, app, mainFont, gridSize);

    double percentageCharted = 0;

#ifdef __linux__
    sf::Context context;

    bool finished = false;

    loadingScreenParams loadingParams(camera, &app, &finished, &percentageCharted);

    /// Setup Simple Loading Screen
    std::future<int> loadingInt = std::async(std::launch::async, loadingScreen, std::ref(loadingParams));
#endif // __linux__

    /// Load Terrain Types
    std::vector<terrainClass> terrains = loadTerrains();

    ///  Load nations, textures, resources & goods using *.txt files
    std::vector<std::shared_ptr<nationClass> > nations = loadNations();
    if(nations.size() == 0)
        app.close();
    std::vector<textureClass> textures = loadTextures();
    if(textures.size() == 0)
        app.close();
    std::vector<resourceClass> resources = loadResources(terrains);
    if(resources.size() == 0)
        app.close();
    std::vector<goodClass> goods = loadGoods(resources);
    if(goods.size() == 0)
        app.close();
    std::vector<buildingClass> buildings = loadBuildings(resources, goods);
    if(buildings.size() == 0)
        app.close();

    /// Setup alpha textures
    std::vector<sf::Texture> alphaTextures;
    for(int i=0; i<4; i++)
    {
        sf::Texture alphaTexture;
        alphaTexture.loadFromFile(std::string("alpha_" + std::to_string(i) + ".png"));
        alphaTextures.push_back(alphaTexture);
    }

///  Generate the grid
        //  Setup timer
        std::clock_t start;
        double duration;
        start = std::clock();

    printf("Creating Grid!...\n");
    std::vector<hexagon> hexs;
    std::vector<townClass> towns;
    std::vector<AIBoat> AIBoats;
    std::vector<unit> units;
    std::vector<int> edgeTiles;
    genGrid(hexs, gridSize, seed, camera, nations, resources, textures, towns, AIBoats, edgeTiles, goods, app);

    for(auto &hex : hexs)
        hex.setupTris(alphaTextures);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Generation Time: "<< duration/4 << "s\n" << std::endl;

/// Perform initial Pathfinidng on generated grid

    std::cout << "Charting the Seas!\n" << std::endl;
    start = std::clock();

    /// Populate tile list and generate paths
    std::vector<hexagon*> townTiles = popTownTiles(towns, hexs, edgeTiles);
    std::vector<std::vector<hexagon*> > townPaths = initPathGen(townTiles, hexs, gridSize, edgeTiles, threads, &percentageCharted);

    duration = (( std::clock() - start ) / (double) CLOCKS_PER_SEC)/4;
    std::cout << "Charting Time: "<< duration/4 << "s\n" << std::endl;


    ///Spawn AI
    spawnBoats(textures, AIBoats, hexs, townPaths, towns, goods);

    ///Setup Player
    sf::Texture playerTexture;
    for(auto &t : textures)
        if(t.name == "playerTexture")
            playerTexture = t;
    playerClass player(playerTexture, hexs, playerName, towns, goods);

    /// Setup HUD & windows
    hudClass HUD(hudView, mainFont, textures);
    auto buttonPos = HUD.tradeDealsButton.getPosition() + sf::Vector2f(12.5, 12.5);
    tradeDealsWindowClass tradeDealsWindow(buttonPos);
    HUD.tradeDealWindow = &tradeDealsWindow;
    hexWindow window(&(hexs.at(0)), camera, mainFont);
    townWindow townWindow(mainFont, textures);
    buildingMenuClass buildingMenu(townWindow, mainFont);

    /// Setup Date & Time System
    Date date;
    double daySpeed = .1; // days last for x sec(s)
    /// Start game clock
    start = std::clock();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    bool paused = false;

#ifdef __linux__
    finished = true;
    loadingInt.get();
#endif // __linux__

    /// Setup shaders
    sf::Shader landBlendShader;
    if(!landBlendShader.loadFromFile("landBlendShader.frag", sf::Shader::Fragment))
        std::cerr << "Failed to load shader: landBlendShader!" << std::endl;

    for(auto &nation : nations)
    {
        if(nation->name != "Portugal")
            nation->atWarWithName = "Portugal";
        else
            nation->atWarWithName = "England";
    }

    /// Game loop
    while (app.isOpen())
    {

        handleEvents(app, hexs, HUD, townWindow, window, player, gridSize, camera, hudView, towns, daySpeed, buildings, textures, buildingMenu, resources, goods, mainFont, paused, AIBoats, units, nations);

        if(!paused)
        {
            ///Update HUD & camera
            HUD.update(player, date);
            update_view(app, camera, hudView, hexs, window, HUD, player, townWindow, AIBoats, buildingMenu, tradeDealsWindow, terrains, landBlendShader, units);

            bool monthTick = false;
            bool yearTick = false;

            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            if(duration >= daySpeed) /// every daytick (a second)
            {
                daytick(HUD, AIBoats, townPaths, date, monthTick, yearTick, player, towns, goods, hexs, gridSize, nations);
                duration = 0;
                start = std::clock();

                for(auto &newUnit : units)
                    printf("Unit at:\t{%i, %i, %i}\n", newUnit.tileOccupying->x, newUnit.tileOccupying->y, newUnit.tileOccupying->z);
            }


            if(monthTick)
            {
                monthtick(towns, goods, townPaths, AIBoats, textures, hexs, nations, buildings, resources);
            }


            if(yearTick)
            {
                yeartick();
            }
        }

        handleEvents(app, hexs, HUD, townWindow, window, player, gridSize, camera, hudView, towns, daySpeed, buildings, textures, buildingMenu, resources, goods, mainFont, paused, AIBoats, units, nations); /// Handle Events when paused



    } /// End of Main Loop

    return EXIT_SUCCESS;
}
