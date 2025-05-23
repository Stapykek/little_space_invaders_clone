#pragma once
#include <SFML/Graphics.hpp>
#include <Object.hpp>
namespace MyGame{
    class Block : public Object{
        private:
            bool inputblocked;
            int m_max_hp;
            int m_hits_from_above;
            int m_hits_from_below;
        public:
            Block();
            ~Block(){
                std::cout << "~Block\n";
            }

            Block(const Block& other) = default;
            Block(std::string _texture_path, int _hp) : 
            Object(_texture_path), m_max_hp(_hp), m_hits_from_above(0),m_hits_from_below(0), inputblocked(false){ //если вдруг есть нормальная текстура
            }
            Block(std::string _texture_path, int _width, int _height, int _hp, int _from_x = 0, int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0) :
            Object(_texture_path, _width, _height, _from_x, _from_y, _frames, _dx, _dy), m_max_hp(_hp), m_hits_from_above(0),m_hits_from_below(0), inputblocked(false){
            }
            void GetDamagedFromBelow();
            void GetDamagedFromAbove();
            void Update() override;
            std::string Type() override;
    };
    void LoadBlocks();
    extern Block basic_block;
    extern Block left_angle_block;
    extern Block right_angle_block;
    extern Block little_middle_block;
}