#pragma once
#include <SFML/Graphics.hpp>
#include <Object.hpp>
#include <Game.hpp>
namespace MyGame{
    class Particle : public Object{
        private:
            float m_frame_time;                 //время кадра
            float m_time_on_frame;              //время, проведённое на кадре анимации
            Owner m_owner;
            float m_lifetime;                   //время жизни частицы
        public:
        ~Particle(){
            std::cout << "~Particle\n";
        }
        Particle(std::string _texture_path, Owner _owner, float _lifetime) : Object(_texture_path), m_lifetime(_lifetime), m_owner(_owner){ //если вдруг есть нормальная текстура
            SetBaseValues();
        }
        Particle(std::string _texture_path, Owner _owner, float _lifetime, int _width, int _height, int _from_x = 0, int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0) :
            Object(_texture_path, _width, _height, _from_x, _from_y, _frames, _dx, _dy), m_owner(_owner), m_lifetime(_lifetime){
            SetBaseValues();
        }
        std::string Type() override;
        void Update() override;
        void Animate();
        void SetBaseValues();
    };

    extern Particle BulletParticle;
    extern Particle ShipParticle;
    extern Particle EnemyParticle;
}