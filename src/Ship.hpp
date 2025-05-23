#pragma once
#include <Object.hpp>
#include <SFML/Graphics.hpp>
namespace MyGame{
    class Ship : public Object{
        private:
            int speed;
            float x0;
            float y0;
            float m_time_since_last_shot;
            float m_shot_frequency;
            float rightbound;
            float leftbound;
            bool shotBlocked;
            void SetBaseValues();
        public:
            Ship(std::string _texture_path) : Object(_texture_path){
                SetBaseValues();
                m_shape.setPosition({x0,y0});
                
            }
            Ship(std::string _texture_path, int _width, int _height, int _from_x = 0, int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0) : 
            Object(_texture_path, _width, _height, _from_x, _from_y, _frames, _dx, _dy){
                SetBaseValues();
                m_shape.setPosition({x0,y0});

            }
            ~Ship(){
                std::cout << "~Ship\n";
            }
            std::string Type() override;
            void Update();
        }; 
}