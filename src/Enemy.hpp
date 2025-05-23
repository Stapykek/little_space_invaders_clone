#pragma once
#include <Object.hpp>
#include <Game.hpp>
namespace MyGame{
    extern int global_flow;     // -1 - влево, 1 - вправо
    extern bool has_shot;
    extern int shot_variant;    // 0 - not decided, 1 - closest, 2 - random
    extern float min_distance;  // расстояние ближайшего врага до кораблика
    class Enemy : public Object{
        private:
            int m_flow;                                 //личный флоу врага, чтобы сравнивать с существующим, и по необходимости менять направление движения
            float m_single_cell_x;                      //расстояние одного движения
            float m_single_cell_y;                      //расстояние одного движения
            float m_base_time_offset;                   //базовое расстояние между движениями(в секундах)
            float m_time_passed_since_movement;         //время с последнего движения
            float m_time_passed_since_last_shot;        //время с последнего выстрела
            float m_leftbound;
            float m_rightbound;
        public:
            Enemy() = delete;
            Enemy(const Enemy& _other) = default;
            ~Enemy(){
                std::cout << "~Enemy\n";
            }

            Enemy(std::string _texture_path, int _width, int _height, int _from_x = 0, 
                            int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0) 
            : Object(_texture_path, _width, _height, _from_x, _from_y, _frames, _dx, _dy) {
                SetBaseValues(); //наконец-то я додумался вынести это в функцию
            }
            
            Enemy(std::string _texture_path) : Object(_texture_path){
                SetBaseValues();
            };
            /* поведение: движутся изначально медленно из 
            стороны в сторону, как только кто-то сталкивается 
            со стенкой, все остальные тоже меняют направление 
            и опускаются на одну клетку вниз, где одна клетка-
            1 ширина/высота врага, тогда они в сторону они за 
            раз двигаются примерно на 1/4 клетки(ещё протестирую)
            нужно создать глобальную переменную или типо того: 
            global_glow, характеризующую сторону, в которую 
            двигаются враги. как только они видят, что она 
            меняется, тогда они скачут вниз на клетку.
            */
            void SetBaseValues();
            std::string Type() override;
            void Update() override;
            void AfterUpdate() override;
            void Animate();
            void Shoot();
    };
    extern Enemy Enemy1;
    extern Enemy Enemy2;
    extern Enemy Enemy3;
    extern Enemy Enemy4;
    extern Enemy* closest;
}