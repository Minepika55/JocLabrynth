#include "Enemy.h"

Enemy::Enemy() : m_speed(100.0f), movingRight(true) {}

void Enemy::init(std::string textureName, sf::Vector2f startPos, sf::Vector2f endPos, float speed) {
    m_texture.loadFromFile(textureName);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(startPos);
    m_startPos = startPos;
    m_endPos = endPos;
    m_speed = speed;
}

void Enemy::update(float dt) {
    sf::Vector2f direction = m_endPos - m_startPos;
    if (movingRight) {
        m_sprite.move(direction / direction.x * m_speed * dt);
        if (m_sprite.getPosition().x >= m_endPos.x) movingRight = false;
    }
    else {
        m_sprite.move(-direction / direction.x * m_speed * dt);
        if (m_sprite.getPosition().x <= m_startPos.x) movingRight = true;
    }
}

sf::Sprite Enemy::getSprite() {
    return m_sprite;
}
