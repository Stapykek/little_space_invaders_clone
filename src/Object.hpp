#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Game.hpp>
namespace MyGame{
    class Object{
        protected: 
            std::vector<std::vector<std::shared_ptr<sf::Texture>>> m_animations;
            /*
            ^ храним умные указатели на текстуры, а не сами текстуры, так мы
            хотя бы оптимизируем префабы(предварительно созданные Object'ы), потому
            что копируя их мы будем копировать умные указатели, а не просто текстуры.
            todo: хранение текстур в одном общем буфере??
            */
            Game* m_game;
            size_t m_curr_animation;
            size_t m_curr_frame;
            sf::RectangleShape m_shape;
            bool m_isAlive;
        public:
            sf::Vector2f GetSize();                                     //получить размер(не то, чтобы нужно, т.к. есть Get, откуда это достаётся)

            void SetPosition(sf::Vector2f _newpos);                     //получить местоположение на сцене
            
            void setSize(sf::Vector2f);                                 //изменить размер

            sf::FloatRect GetGlobalBounds();                            //получить границы объекта на поле

            const sf::RectangleShape& Get();                            //получить m_shape, без возможности изменить его

            virtual std::string Type() = 0;                             //тип объекта

            virtual void Update() = 0;                                  //обновление состояния объекта

            virtual void AfterUpdate();                                 //вторичное обновление

            void Animate();                                             //анимирование объекта

            void SetFrame(int _frame);                                  //установка кадра

            void SetAnimation(int _anim, int _frame);                   //установка анимации (и кадра).

                                                                        //базовые конструктор и деструктор
            Object() = default;
            virtual ~Object() = default;                                

                                                                        //констурктор копирования
            Object(const Object& _other)=default;
            /*{
                m_isAlive = _other.m_isAlive;
                m_game = _other.m_game;
                m_curr_animation = _other.m_curr_animation;
                m_curr_frame = _other.m_curr_frame;
                m_shape = _other.m_shape;
                for(std::vector<std::shared_ptr<sf::Texture>> anim : _other.m_animations){
                    m_animations.push_back(std::vector<std::shared_ptr<sf::Texture>>());
                    for(std::shared_ptr<sf::Texture> texture : anim){
                        m_animations.back().push_back(texture);
                        // std::cout << "someclass " << texture.use_count() << "\n"; // насколько я заметил, с счётчиком проблем нет.
                    }
                }
            }// это вроде не нужно*/
            Object& operator=(const Object& _other) = delete;            //не хочу возиться со swap для этого и дочерних классов, сейчас у меня работа с одними лишь указателями, так что с этим проблем быть не должно
            Object(std::string _texture_path, int _width, int _height, int _from_x = 0, int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0) : m_curr_animation(0), m_curr_frame(0), m_isAlive(true){
                std::vector<std::shared_ptr<sf::Texture>> textures;     //временный вектор для текстур анимации
                for (int i = 0; i < _frames; i++){                      //загрузка текстур с листа спрайтов, с уведомлениями.
                    textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
                    if(!textures.back()->loadFromFile(_texture_path, false, sf::IntRect({_from_x + i*_dx,_from_y + i*_dy},{_width,_height}))){
                        std::cout << "couldn't load from file" << " " ;
                    }
                    else{
                        std::cout << "loaded from: " << _texture_path << "\nsize: "<< textures.back()->getSize().x << " " << textures.back()->getSize().y << "\n";
                    }
                }
                m_shape = sf::RectangleShape({float(_width), float(_height)});  //задаём прямоугольник, представляющий наш объект
                m_animations.push_back(textures);                               //добавляем ему первой анимацией нашу подгруженную анимацию
                m_shape.setTexture(m_animations[0][0].get());                   //ну и ставим начальную текстуру объекту
                m_shape.setOrigin({m_shape.getSize().x/2,m_shape.getSize().y/2});
            }
                                                                        //загрузка текстуры из изображения
            Object(std::string _texture_path) : m_curr_animation(0), m_curr_frame(0), m_isAlive(true){ 
                m_animations.resize(1);
                m_animations.back().push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
                if(!m_animations.back().back()->loadFromFile(_texture_path)){
                    std::cout << "couldn't load from file" << " " ;
                }
                else{
                    std::cout << "loaded from: " << _texture_path << "\nsize: "<< m_animations.back().back()->getSize().x << " " <<  m_animations.back().back()->getSize().y << "\n";
                }
                m_shape = sf::RectangleShape({float(m_animations[0][0]->getSize().x), float(Object::m_animations[0][0]->getSize().y)});
                m_shape.setTexture(m_animations[0][0].get());
                m_shape.setOrigin({m_shape.getSize().x/2,m_shape.getSize().y/2});
            }
            void AddFramesToAnimation(std::string _texture_path, int _width, int _height, unsigned int _anim_where, int _from_x,  int _from_y, unsigned int _frames_howmany, int _dx, int _dy);
            void AddFrameToAnimation(std::string _texture_path, unsigned int _anim_where);
            void AddAnimation(std::string _texture_path, int _width, int _height, int _from_x, int _from_y , int _frames, int _dx, int _dy);
            void Set_Game(Game* _game);
            const bool IsAlive();
            void Kill();
    };
}

