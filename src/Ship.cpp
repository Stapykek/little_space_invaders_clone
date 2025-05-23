#include <iostream>
#include <Ship.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Object.hpp>
#include <Game.hpp>
#include <Timer.hpp>
#include <Bullet.hpp>
namespace MyGame{

    std::string Ship::Type(){
        return "Ship";
    }
    void Ship::Update(){
        float dt = Time.Get_Delta_Time();
        sf::Vector2f velocity = {0,0};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            velocity -= sf::Vector2f(speed*dt,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            velocity += sf::Vector2f(speed*dt,0);
        }
        m_shape.move(velocity);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !shootBlocked){
        //     std::cout << "Space pressed\n";
        //     shootBlocked = true;
        //     //Bullet* newbul = new Bullet("spritesheet.png", -300.0f, 1,6,120,54); <- old code
        //     Bullet* newbul = new Bullet(PlayerBullet);
        //     newbul -> SetPosition(m_shape.getPosition());
        //     newbul -> SetBounds(0, 320.0f);
        //     m_game -> Spawn(newbul);
        // }
        // if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        //     shootBlocked = false;
        // }
        if (shotBlocked){
            m_time_since_last_shot += Time.Get_Delta_Time();
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_time_since_last_shot >= m_shot_frequency){
            m_time_since_last_shot = 0;
            shotBlocked = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !shotBlocked){
            std::cout << "Up pressed\n";
            shotBlocked = true;
            Bullet* newbul = new Bullet(PlayerBullet);
            newbul -> SetPosition(m_shape.getPosition());
            m_game -> Spawn(newbul);
        }
        


        if(m_shape.getPosition().x > rightbound){
            m_shape.setPosition({rightbound, m_shape.getPosition().y});
        }
        if(m_shape.getPosition().x < leftbound){
            m_shape.setPosition({leftbound, m_shape.getPosition().y});
        }
    }

    void Ship::SetBaseValues(){
        speed = 90;
        x0 = 140.0;
        y0 = 220.0;
        m_time_since_last_shot = 0;
        shotBlocked = false;
        m_shot_frequency = 1.f; //выстрел 1 раз в секунду
        rightbound = game_width*3/4 - m_shape.getSize().x / 2.0f;
        leftbound = 10 + m_shape.getSize().x / 2.0f;
    }
}