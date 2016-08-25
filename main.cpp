#include "custom.h"

int main(int argc, char* argv[])
{
    /// Create the main window
    sf::RenderWindow app(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Carribbean"/*, sf::Style::Fullscreen*/);

    /// Gather available threads
    unsigned threads = std::thread::hardware_concurrency();
    if(threads==0){threads=1;} // 0 Returned if # of threads undetectable, in such a case future code is unusable so threads must be set
    printf("\n\n\tFound %u threads\n\n", threads);

    /// Setup initial gridSize
    int gridSize=50; //100 default reduced for testing
    int seed=time(NULL); // default seed for rand, gets current time unless overridden by arg
    std::string playerName;
    if(argc > 1)
        gridSize = atoi(argv[1]);
    if(argc > 2)
        seed = atoi(argv[2]);
    if(argc > 3)
        playerName = argv[3];

    if(gridSize % 2 != 0)
        gridSize += 1; // Gridsize must be even for adjacent Tile calculations


    ///  Setup Cameras
    sf::View camera;
    sf::View hudView;
    sf::Font mainFont;
    cameraInit(camera, hudView, app, mainFont, gridSize);

    /// Load Terrain Types
    std::vector<terrainClass> terrains = loadTerrains();

    ///  Load nations, textures, resources & goods using *.txt files
    std::vector<nationClass> nations = loadNations();
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


///  Generate the grid
        //  Setup timer
        std::clock_t start;
        double duration;
        start = std::clock();

    printf("Creating Grid!...\n");
    std::vector<hexagon> hexs;
    std::vector<townClass> towns;
    std::vector<AIBoat> AIBoats;
    std::vector<int> edgeTiles;
    genGrid(hexs, gridSize, seed, camera, nations, resources, textures, towns, AIBoats, edgeTiles, goods);

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Generation Time: "<< duration/4 << "s\n" << std::endl;

/// Perform initial Pathfinidng on generated grid

    std::cout << "Charting the Seas!\n" << std::endl;
    start = std::clock();

    /// Populate tile list and generate paths
    std::vector<hexagon*> townTiles = popTownTiles(towns, hexs, edgeTiles);
    std::vector<std::vector<hexagon*> > townPaths = initPathGen(townTiles, hexs, gridSize, edgeTiles, threads);

    duration = (( std::clock() - start ) / (double) CLOCKS_PER_SEC)/4;
    std::cout << "Charting Time: "<< duration/4 << "s\n" << std::endl;


    ///Spawn AI
    spawnBoats(textures, AIBoats, hexs, townPaths, towns, goods);

    ///Setup Player
    sf::Texture playerTexture;
    playerTexture.loadFromFile("tobacco.png");
    playerClass player(playerTexture, hexs, playerName, towns, goods);

    /// Setup HUD & windows
    hudClass HUD(hudView, mainFont);
    hexWindow window(&(hexs.at(0)), camera, mainFont);
    townWindow townWindow(mainFont, textures);
    buildingMenuClass buildingMenu(townWindow, mainFont);

    /// Setup Date & Time System
    Date date;
    double daySpeed = 1; // days last for x sec(s)
    /// Start game clock
    start = std::clock();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;


    /// Game loop
    while (app.isOpen())
    {
        handleEvents(app, hexs, townWindow, window, player, gridSize, camera, hudView, towns, daySpeed, buildings, textures, buildingMenu, resources, goods);


        ///Update HUD & camera
        HUD.update(player, date);
        update_view(app, camera, hudView, hexs, window, HUD, player, townWindow, AIBoats, buildingMenu);

        bool monthTick = false;
        bool yearTick = false;

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        if(duration >= daySpeed) /// every daytick (a second)
        {
            daytick(HUD, AIBoats, townPaths, date, monthTick, yearTick, player, towns, goods);
            duration = 0;
            start = std::clock();
        }


        if(monthTick)
        {
            monthtick(towns, hexs, resources, goods, townPaths);
        }


        if(yearTick)
        {
            yeartick();
        }




    } /// End of Main Loop

    return EXIT_SUCCESS;
}
