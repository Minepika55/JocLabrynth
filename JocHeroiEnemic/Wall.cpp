#include "Wall.h"

Wall::Wall() : m_speed(50.0f), movingUp(true) {}

void Wall::init(std::string textureName, sf::Vector2f startPos, sf::Vector2f endPos, float speed) {
    m_texture.loadFromFile(textureName);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(startPos);
    m_startPos = startPos;
    m_endPos = endPos;
    m_speed = speed;
}

void Wall::update(float dt) {
    sf::Vector2f direction = m_endPos - m_startPos;
    if (movingUp) {
        m_sprite.move(direction / direction.y * m_speed * dt);
        if (m_sprite.getPosition().y >= m_endPos.y) movingUp = false;
    }
    else {
        m_sprite.move(-direction / direction.y * m_speed * dt);
        if (m_sprite.getPosition().y <= m_startPos.y) movingUp = true;
    }
}

sf::Sprite Wall::getSprite() {
    return m_sprite;
}
