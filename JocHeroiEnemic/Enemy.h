#pragma once

#include "SFML/Graphics.hpp"

class Enemy {
public:
    Enemy();
    void init(std::string textureName, sf::Vector2f startPos, sf::Vector2f endPos, float speed);
    void update(float dt);
    sf::Sprite getSprite();

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Vector2f m_startPos, m_endPos;
    float m_speed;
    bool movingRight;
};

