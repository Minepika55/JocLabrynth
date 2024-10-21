#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include "Hero.h"
#include "TextureHolder.h"
#include "Enemy.h"
#include "Wall.h"

class Engine {
private:
    TextureHolder holder;
    sf::Vector2f viewSize;
    sf::RenderWindow window;

    sf::Sprite skySprite;
    sf::Sprite bgSprite;

    Hero hero;
    float currentTime = 0.0f;

    int score = 0;
    bool gameover = false;
    bool win = false;

    sf::Font headingFont;
    sf::Font scoreFont;

    sf::Text headingText;
    sf::Text scoreText;
    sf::Text tutorialText;

    sf::Music bgMusic;
    sf::SoundBuffer fireBuffer;
    sf::SoundBuffer hitBuffer;
    sf::Sound fireSound;
    sf::Sound hitSound;

    std::vector<Enemy> enemies;
    std::vector<Wall> Walls;

    void reset();
    void init();
    void updateInput();
    void update(float dt);
    void draw();
    bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
    void spawnEnemies();
    void moveEnemies(float dt);
    void moveWalls(float dt);
    void gameOver();
    void Winner();

public:
    Engine();
    ~Engine();
    int run();
};
