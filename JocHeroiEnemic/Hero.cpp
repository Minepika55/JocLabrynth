#include "Hero.h"

Hero::Hero() : m_horizontalVelocity(0.0f) {}

Hero::~Hero() {}

void Hero::init(std::string textureName, sf::Vector2f position, float mass) {
    m_position = position;
    m_mass = mass;
    m_grounded = false;
    m_texture.loadFromFile(textureName.c_str());
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_position);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Hero::update(float dt) {
    // Apply gravity
    m_velocity -= m_mass * m_gravity * dt;

    // Update vertical position
    m_position.y -= m_velocity * dt;

    // Update horizontal position
    m_position.x += m_horizontalVelocity * dt;

    m_sprite.setPosition(m_position);

    // Prevent the hero from falling below the ground
    if (m_position.y >= 768 * 0.75f) {
        m_position.y = 768 * 0.75f;
        m_velocity = 0;
        m_grounded = true;
        jumpCount = 0;
    }

    //Evitar que poguem sortir de la pantalla
    if (m_position.x < 0) {
        m_position.x = 0;
    }

    //Que no poguem sortir per dalt
    if (m_position.y < 0) {
        m_position.y = 0;
    }

}

//Salt del jugador
void Hero::jump(float velocity) {
    if (jumpCount < 2) {
        jumpCount++;
        m_velocity = velocity;
        m_grounded = false;
    }
}

//Moviments horitzontals
void Hero::moveLeft(float velocity) {
    m_horizontalVelocity = -velocity;
}

void Hero::moveRight(float velocity) {
    m_horizontalVelocity = velocity;
}

sf::Sprite Hero::getSprite() {
    return m_sprite;
}
