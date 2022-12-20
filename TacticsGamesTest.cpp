// TacticsGamesTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>

std::vector<sf::Texture> loadTileSet(const std::string& fileName, int tileSize);
std::vector<sf::Sprite> createTileSprites(const std::vector<sf::Texture>& tiles);
std::vector<std::vector<sf::Sprite>> createMap(int width, int height, const std::vector<sf::Sprite>& sprites);

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TacticsGamesTest");
    std::vector<sf::Texture> tileSet = loadTileSet("basicTileSet.png", 16);
    std::vector<sf::Sprite> tileSprites = createTileSprites(tileSet);

    //generate the map using the createMap function
    std::vector<std::vector<sf::Sprite>> map = createMap(20, 20, tileSprites);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        window.clear();

        /*sf::Transform isoTransform;
        isoTransform.translate(window.getSize().x / 2, window.getSize().y / 2);
        isoTransform.rotate(-45.0f);
        isoTransform.scale(0.5f,0.5f);*/

        for (int x = 0; x < map.size(); x++) {
            for (int y = 0; y < map[x].size(); y++) {
                sf::Sprite& sprite = map[x][y];
                window.draw(sprite);
            }
        }

        /*for (auto& sprite : tileSprites) {
            sprite.setPosition(xOffset, 0.0f);
            window.draw(sprite);
            xOffset += sprite.getGlobalBounds().width;
        }*/

        /*for (const auto& sprite : tileSprites) {
            window.draw(sprite);
        }*/
        window.display();
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
        int y = (i / numOfTilesX) * tileSize;

        sf::Texture tile;
        if (!tile.create(tileSize, tileSize)) {
            std::cout << "Error creating a tile texture" << std::endl;
            return{};
        }
        if (!tile.loadFromImage(tileSetImage, sf::IntRect(x, y, tileSize, tileSize))) {
            std::cout << "Error loading tile texture from image" << std::endl;
            return{};
        }
        /*tile.create(tileSize, tileSize);
        tile.loadFromImage(tileSetImage, sf::IntRect(x,y,tileSize,tileSize));*/
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

std::vector<std::vector<sf::Sprite>> createMap(int width, int height, const std::vector<sf::Sprite>& sprites) {
    std::vector<std::vector<sf::Sprite>> map(width, std::vector<sf::Sprite>(height));

    int value = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            sf::Sprite& sprite = map[x][y];
            sprite = sprites[value];
            sprite.setPosition(x * sprite.getGlobalBounds().width, y * sprite.getGlobalBounds().height);
            value = (value + 1) % sprites.size();
        }
    }
    return map;
}