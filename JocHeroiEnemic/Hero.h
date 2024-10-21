#pragma once

#include <SFML/Graphics.hpp>

class Hero {

public:
    Hero();
    ~Hero();

    void init(std::string textureName, sf::Vector2f position, float mass);
    void update(float dt);
    void jump(float velocity);
    void moveLeft(float velocity);
    void moveRight(float velocity);
    sf::Sprite getSprite();

private:
    int jumpCount = 0;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    float m_mass;
    float m_velocity;      
    float m_horizontalVelocity;  
    const float m_gravity = 9.80f;
    bool m_grounded;
    int m_frameCount;
    float m_animDuration;

    float m_elapsedTime;
    sf::Vector2i m_spriteSize;
};
