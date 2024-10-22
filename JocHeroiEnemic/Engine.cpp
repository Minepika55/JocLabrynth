#include "Engine.h"

Engine::Engine() {
    // Get the screen resolution and create an SFML window and View
    viewSize.x = 1024;
    viewSize.y = 768;
    window.create(sf::VideoMode(viewSize.x, viewSize.y),
        "APPLEMAGEDDON",
        sf::Style::Default);
}

Engine::~Engine() {}

void Engine::init() {
    // Load background textures
    skySprite = Sprite(TextureHolder::GetTexture("Assets/graphics/sky.png"));
    bgSprite = Sprite(TextureHolder::GetTexture("Assets/graphics/bg.png"));

    // Load font
    headingFont.loadFromFile("Assets/fonts/Deathrecord.ttf");
    scoreFont.loadFromFile("Assets/fonts/SCE.ttf");

    // Set Heading Text
    headingText.setFont(headingFont);
    headingText.setString("APPLE ULTIMATUM");
    headingText.setCharacterSize(84);
    headingText.setFillColor(sf::Color::Red);
    sf::FloatRect headingBounds = headingText.getLocalBounds();
    headingText.setOrigin(headingBounds.width / 2, headingBounds.height / 2);
    headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));

    // Set Tutorial Text
    tutorialText.setFont(scoreFont);
    tutorialText.setString("Fletxa avall per inciar");
    tutorialText.setCharacterSize(35);
    tutorialText.setFillColor(sf::Color::Red);
    sf::FloatRect tutorialBounds = tutorialText.getLocalBounds();
    tutorialText.setOrigin(tutorialBounds.width / 2, tutorialBounds.height / 2);
    tutorialText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.20f));

    // Audio
    bgMusic.openFromFile("Assets/audio/bgMusic.ogg");
    bgMusic.play();
    hitBuffer.loadFromFile("Assets/audio/hit.ogg");
    fireBuffer.loadFromFile("Assets/audio/fire.ogg");

    // Initialize the player
    hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);

    //Spawneja els enemis
    spawnEnemies();

    //Engega les parets
    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(500, 400), sf::Vector2f(500, 600), 80.0f);
    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(500, 400), sf::Vector2f(500, 600), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(800, 200), sf::Vector2f(700, 400), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(1500, 150), sf::Vector2f(900, 250), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(900, 350), sf::Vector2f(900, 150), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(50, 350), sf::Vector2f(200, 600), 80.0f);


    srand(static_cast<unsigned int>(time(0)));
}

void Engine::spawnEnemies() {
    //Spawn enemic
    enemies.push_back(Enemy());
    enemies.back().init("Assets/graphics/enemy.png", sf::Vector2f(300, 500), sf::Vector2f(600, 500), 50.0f);
}

//Controls del jugador
void Engine::updateInput() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                hero.jump(750.0f);
            }
            if (event.key.code == sf::Keyboard::Down) {
                if (gameover) {
                    gameover = false;
                    reset();
                }
            }
            if (event.key.code == sf::Keyboard::Left) {
                hero.moveLeft(300.0f);
            }
            if (event.key.code == sf::Keyboard::Right) {
                hero.moveRight(300.0f);
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
                hero.moveLeft(0);
                hero.moveRight(0);
            }
        }

        if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)//Per tencar el joc
            window.close();
    }
}

void Engine::update(float dt) {
    hero.update(dt);

    currentTime += dt;

    //Mou tot
    moveEnemies(dt);
    moveWalls(dt);

    //Mirem colisions
    for (auto& enemy : enemies) {
        if (checkCollision(hero.getSprite(), enemy.getSprite())) {
            gameOver();
        }
    }

    for (auto& wall : Walls) {
        if (checkCollision(hero.getSprite(), wall.getSprite())) {
            gameOver();
        }
    }

    //Mirem si el jugador guanya
    if (hero.getSprite().getPosition().x + hero.getSprite().getGlobalBounds().width >= viewSize.x) {
        Winner();
    }

}

void Engine::moveEnemies(float dt) {//Actualitza el moviment enemic
    for (auto& enemy : enemies) {
        enemy.update(dt);
    }
}

void Engine::moveWalls(float dt) {
    for (auto& wall : Walls) {
        wall.update(dt);
    }
}

//Dibuixa el joc
void Engine::draw() {
    window.clear(sf::Color::Red);
    window.draw(skySprite);
    window.draw(bgSprite);

    window.draw(hero.getSprite());

    if (gameover) {
        window.draw(headingText);
        window.draw(tutorialText);
    }
    else {
        window.draw(scoreText);
    }

    //Dibuixa enemics
    for (auto& enemy : enemies) {
        window.draw(enemy.getSprite());
    }

    //Dibuixa les parets
    for (auto& wall : Walls) {
        window.draw(wall.getSprite());
    }

    window.display();
}

//Inicialitza el temps del joc
int Engine::run() {
    sf::Clock clock;
    init();

    while (window.isOpen()) {
        updateInput();

        sf::Time dt = clock.restart();

        if (!gameover) {
            update(dt.asSeconds());
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {//Per reiniciar
                gameover = false;
                reset();
            }
        }

        draw();
    }

    return 0;
}

//Colisions
bool Engine::checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
    sf::FloatRect shape1 = sprite1.getGlobalBounds();
    sf::FloatRect shape2 = sprite2.getGlobalBounds();

    return shape1.intersects(shape2);
}

//Reinici del joc
void Engine::reset() {
    score = 0;
    currentTime = 0.0f;


    scoreText.setString("Score: 0");

    //Reinicia tot
    hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);

    //Reinicia enemics
    enemies.clear();
    spawnEnemies();

    //Reinicia walls
    Walls.clear();
    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(500, 400), sf::Vector2f(500, 600), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(800, 200), sf::Vector2f(700, 400), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(1500, 150), sf::Vector2f(900, 250), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(900, 350), sf::Vector2f(900, 150), 80.0f);

    Walls.push_back(Wall());
    Walls.back().init("Assets/graphics/wall.png", sf::Vector2f(50, 350), sf::Vector2f(200, 600), 80.0f);

}

//Fa el GameOver
void Engine::gameOver() {
    gameover = true;
    headingText.setString("Game Over!");
    tutorialText.setString("Press Down to Restart");
}

//Victoria
void Engine::Winner() {
    win = true;
    headingText.setString("WINNER!");
    tutorialText.setString("Press Down to play again");
}
