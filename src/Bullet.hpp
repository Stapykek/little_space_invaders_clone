#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Object.hpp>
#include <Game.hpp>
namespace MyGame{
    class Bullet : public Object{
        private:
            Owner m_owner;                      //кто выстрелил пулю? игрок или враг
            float m_speed;
            float upperbound;
            float lowerbound;
            float m_frame_changing_frequency;   //скорость анимации
            float m_time_on_frame;              //время, проведённое на кадре анимации
        public:
            Bullet(const Bullet& other) = default;
            Bullet& operator=(const Bullet& other)=default;
            Bullet(Bullet&& other) = default;
            void SetBaseValues();
            ~Bullet(){
                std::cout << "~Bullet\n";
            }
            Bullet(std::string _texture_path, float _speed, Owner _owner) : Object(_texture_path), m_speed(_speed), m_owner(_owner){ //если вдруг есть нормальная текстура
                SetBaseValues();
            }
            Bullet(std::string _texture_path,  float _speed, Owner _owner, int _width, int _height, int _from_x = 0, int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0) :
            Object(_texture_path, _width, _height, _from_x, _from_y, _frames, _dx, _dy), m_speed(_speed), m_owner(_owner){
                SetBaseValues();
            }
            std::string Type() override;
            void Update() override;
            void Animate();
    };

    extern const Bullet PlayerBullet;
    extern const std::vector<Bullet> EnemyBullets;
}