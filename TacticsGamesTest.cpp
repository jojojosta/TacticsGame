// TacticsGamesTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <SFML/OpenGL.hpp>

std::vector<sf::Texture> loadTileSet(const std::string& fileName, int tileSize);
std::vector<sf::Sprite> createTileSprites(const std::vector<sf::Texture>& tiles);

int main()
{

    std::vector<sf::Texture> tileSet = loadTileSet("basicTileSet.png", 16);
    std::vector<sf::Sprite> tileSprites = createTileSprites(tileSet);
    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "My Window");


    while (mainWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                mainWindow.close();
            }

        }
        mainWindow.clear();

        for (const auto& sprite : tileSprites) {
            mainWindow.draw(sprite);
        }
        mainWindow.display();
    }
return 0;
}

//function definition

std::vector<sf::Texture> loadTileSet(const std::string& fileName, int tileSize) {
    sf::Image tileSetImage;
    if (!tileSetImage.loadFromFile(fileName)) {
        std::cout << "Error loading tile set image" << std::endl;
        return {};
    }

    //get the dimensions of the tile set image
    int width = tileSetImage.getSize().x;
    int height = tileSetImage.getSize().y;

    //calculate the number of tiles in the tile set
    int numOfTilesX = width / tileSize;
    int numOfTilesY = height / tileSize;
    int numOfTiles = numOfTilesX * numOfTilesY;

    //create a vector to hold the tile textures
    std::vector<sf::Texture> tiles(numOfTiles);
    //load each tile into a texture
    for (int i = 0; i < numOfTiles; i++) {
        int x = (i % numOfTilesX) * tileSize;
        int y = (i / numOfTilesY) * tileSize;

        sf::Texture tile;
        tile.create(tileSize, tileSize);
        tile.loadFromImage(tileSetImage, sf::IntRect(x,y,tileSize,tileSize));
        tiles[i] = tile;
    }
    return tiles;

}
std::vector<sf::Sprite> createTileSprites(const std::vector<sf::Texture>& tiles) {
    std::vector<sf::Sprite> sprites;

    for (const auto& texture : tiles) {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprites.push_back(sprite);
    }
    return sprites;
}