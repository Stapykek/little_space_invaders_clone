#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
namespace MyGame{
    extern unsigned int game_width;
    extern unsigned int game_height;
    extern float enemy_start_x;
    extern float enemy_dx;
    extern float enemy_start_y;
    extern float enemy_dy;
    enum class Owner{
        Player,
        Enemy,
        Bullet
    };
    enum class GameState{
        Active,
        Win,
        Loss
    };
    class Object;
                /*      Предварительное объявление класса Object, чтобы избавиться от циклической зависимости,
                        которая возникает из-за m_objects здесь и m_game в классе Object.
                        комментарий с реддита: 
                        For a novice (which you seem to be), a simple recipe to follow is: "if you have two structures who have a pointer/référence to one another, 
                        put each in their own file and forward-declare the other in it". Спасибо..
                        Вообще циклические зависимости это, похоже, не очень хорошо... но тут никак без этого
                */ 
    class Game{
        private:
            int m_enemy_cnt;
            GameState m_state;
            sf::RenderWindow m_window;
            std::vector<std::shared_ptr<Object>> m_objects; /* чтобы засунуть в все дочерние классы в один контейнер, нужно чтобы этот контейнер хранил указатели(
                                                            или умные указатели) на родительский класс, а не его объекты, иначе произойдёт "срезка":
                                                            скопируются лишь элементы относящиеся к родительскому классу*/
            void DestroyAll();
            
        public:
            Game(Game& _other) = delete;
            Game& operator=(Game& _other) = delete;
            Game(uint32_t _width,
            uint32_t _height, 
            std::string _name){
            m_window.create(sf::VideoMode({game_width, game_height}), _name); //внутреннее разрешение игры - 320 х 240 (я всё-таки копирую аркадную игру из 1978...)
            m_window.setSize({_width,_height});
            m_window.setPosition({int(sf::VideoMode::getDesktopMode().size.x - _width)/2,int(sf::VideoMode::getDesktopMode().size.y - _height)/2});
            m_window.setFramerateLimit(144);
            }
            void CountEnemies();
            const int GetEnemyCount();
            void UpdateScene();
            void DrawScene();
            void Run();
            void SetState(GameState _state);
            void foo();
            std::vector<std::shared_ptr<Object>> Find(std::string _type);

            template <typename T>
            void Spawn(T* _obj){
                if(dynamic_cast<Object*>(_obj) == nullptr){
                    std::cout << "not an object\n"; //мы не можем заспавнить не объект
                    return;
                }
                m_objects.push_back(std::shared_ptr<Object>(_obj));
                _obj->Set_Game(this);
            }

            template<typename T>
            void Despawn(T* _obj){
                if(dynamic_cast<Object*>(_obj) == nullptr){
                    std::cout << "not even an object\n"; //это даже не объект..
                    return;
                }
                size_t n = m_objects.size(); //считаем число объектов. мы можем это сделать, т.к. удалим всего лишь один объект
                for(size_t i = 0; i<n; i++){
                    if(dynamic_cast<T*>(m_objects[i].get())!= nullptr){
                        if (m_objects[i].get() == _obj){
                            m_objects.erase(m_objects.begin() + i);
                            break;
                        }
                    }
                    // else{
                    //     std::cout << "Not a " << _obj->Type() << ".\n";
                    // } //для дебага
                    if (i==n-1){
                        std::cout << "this object is not present in the scene\n";
                    }
                }
            }

            std::vector<std::shared_ptr<Object>> CheckCollisions(Object* _obj, std::string _object_type);

    };
        
}

