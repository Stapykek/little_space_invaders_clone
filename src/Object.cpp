#include <SFML/Graphics.hpp>
#include <Object.hpp>
#include <Game.hpp>
namespace MyGame{
    void Object::Update(){}
    void Object::Set_Game(Game* _game){
        m_game = _game;
    }
    const sf::RectangleShape& Object::Get(){
        return m_shape;
    }
    //установка кадра
    void Object::SetFrame(int _frame){
        if (_frame < 0 ){
            std::cout << "Don't set negative values " << _frame << "\n";
            return;
        }
        //простая проверка
        if (_frame < m_animations[m_curr_animation].size()){ 
            m_curr_frame = _frame;
            m_shape.setTexture(m_animations[m_curr_animation][_frame].get());
        }
        else{
            //вывод ошибки
            std::cout << "Can't set frame number " << _frame << " for an Object with " << m_animations[m_curr_animation].size() << "frames.\n";  
        }

    }
    //установка и анимации(и кадра)
    void Object::SetAnimation(int _animation, int _frame = 0){
        if (_animation < 0 || _frame < 0 ){
            std::cout << "Don't set negative values " << _animation << " " << _frame << "\n";
            return;
        }
        //простая проверка
        if (_frame < m_animations[m_curr_animation].size()){ 
            m_curr_animation = _animation;
            SetFrame(_frame);
            return;
        }
        else{
            //вывод ошибки
            std::cout << "Can't set animation " << _animation << " for an Object with " << m_animations[m_curr_animation].size() << "frames.\n";  
        }

    }

    void Object::AddAnimation(std::string _texture_path, int _width, int _height, int _from_x = 0, int _from_y = 0, int _frames = 1, int _dx = 0, int _dy = 0){
        m_animations.push_back(std::vector<std::shared_ptr<sf::Texture>>());
        //загрузка с листа спрайтов                
        for (int i = 0; i < _frames; i++){
                    m_animations.back().push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
                    if(!m_animations.back().back()->loadFromFile(_texture_path, false, sf::IntRect({_from_x + i*_dx,_from_y + i*_dy},{_width,_height}))){
                        std::cout << "couldn't load from file" << " " ;
                    }
                    else{
                        std::cout << "loaded from: " << _texture_path << "\nsize: "<< m_animations.back().back()->getSize().x << " " << m_animations.back().back()->getSize().y << "\n";
                    }
        }
        }
    
    void Object::AddFramesToAnimation(std::string _texture_path, int _width, int _height, unsigned int _anim_where ,
        int _from_x = 0, int _from_y = 0, unsigned int _frames_howmany = 1 , int _dx = 0, int _dy = 0){
        std::vector<std::shared_ptr<sf::Texture>> textures;
        //загрузка с листа спрайтов                
        for (int i = 0; i < _frames_howmany; i++){
            textures.push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
            if(!textures[i].get()->loadFromFile(_texture_path, false, sf::IntRect({_from_x + i*_dx,_from_y + i*_dy},{_width,_height}))){
                std::cout << "couldn't load from file" << " " ;
            }
            else{
                std::cout << "loaded from: " << _texture_path << "\nsize: "<< textures.back()->getSize().x << " " << textures.back()->getSize().y << "\n";
            }
        }
    }

    void Object::AddFrameToAnimation(std::string _texture_path, unsigned int _anim_where){
        if (_anim_where << m_animations.size()){
            m_animations[_anim_where].push_back(std::shared_ptr<sf::Texture>(new sf::Texture));
                if(!m_animations[_anim_where].back()->loadFromFile(_texture_path, false)){
                    std::cout << "couldn't load from file" << "\n" ;
                }
                else{
                    std::cout << "loaded from: " << _texture_path << "\nsize: "<< m_animations[_anim_where].back()->getSize().x << " " << m_animations[_anim_where].back()->getSize().y << "\n";
                }
        }
        else{
            std::cout << "Can't add to animation " << _anim_where << " for " << this->Type() << " which has " << m_animations.size() << " animations\n";
        }
    }

    void Object::SetPosition(sf::Vector2f _newpos){
        m_shape.setPosition(_newpos);
    }
    
    sf::Vector2f Object::GetSize(){
        return m_shape.getSize();
    }

    sf::FloatRect Object::GetGlobalBounds(){
        return m_shape.getGlobalBounds();
    }

    void Object::setSize(sf::Vector2f _newsize){
        m_shape.setSize(_newsize);
    }

    const bool Object::IsAlive(){
        return m_isAlive;
    }
    void Object::Kill(){
        m_isAlive = false;
    }

    void Object::AfterUpdate(){

    }
}