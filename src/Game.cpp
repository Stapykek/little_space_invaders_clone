#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Object.hpp>
#include <Game.hpp>
#include <Ship.hpp>
#include <Timer.hpp>
namespace MyGame{
    
    void Game::Run(){
        sf::Font font;
        m_state = GameState::Active;
        if(!font.openFromFile("Font.ttf")){
            std::cout << "проблема со шрифтом...";
        }
        sf::Text win_text(font);
        win_text.setCharacterSize(24);
        win_text.setString(L"Вы победили!");
        win_text.setOrigin(win_text.getGlobalBounds().getCenter());
        win_text.setPosition({float(game_width)/2,float(game_height)/2});
        sf::Text loss_text(font);
        loss_text.setCharacterSize(24);
        loss_text.setString(L"Вы проиграли!");
        loss_text.setOrigin(loss_text.getGlobalBounds().getCenter());
        loss_text.setPosition({float(game_width)/2,float(game_height)/2});
        while (m_window.isOpen()){
            while (const std::optional event = m_window.pollEvent()){
                if (event->is<sf::Event::Closed>()){
                    m_window.close();
                    DestroyAll();
                }
            }
            m_window.clear();
            switch (m_state){
            case GameState::Active:
                CountEnemies();
                UpdateScene();
                DrawScene();
                Time.Update_Delta_Time();
                break;
            case GameState::Win:
                m_window.draw(win_text);
                break;
            case GameState::Loss:
                m_window.draw(loss_text);
                break;
        }
        m_window.display();
    }
    }
    std::vector<std::shared_ptr<Object>> Game::Find(std::string _type){
        std::vector<std::shared_ptr<Object>> found;
        for(std::shared_ptr<Object> obj : m_objects){
            if(obj->Type() == _type){
                found.push_back(obj);
            }
        }
        return found;
    }
    void Game::foo(){
        std::cout << m_window.getSize().x << " " << m_window.getSize().y << "\n";
    }
    void Game::UpdateScene(){
        for(int i = 0; i<m_objects.size(); i++){ 
            if(!m_objects[i]->IsAlive()){
                std::swap(m_objects[i], m_objects.back());
                m_objects.pop_back();
                i--;
            }
        }
        for(int i = 0; i<m_objects.size(); i++){ 
            m_objects[i]->Update();
        }
        for(int i = 0; i<m_objects.size(); i++){ 
            m_objects[i]->AfterUpdate();
        }
    }
    void Game::DrawScene(){
        for(size_t i = 0; i<m_objects.size(); i++){
            m_window.draw(m_objects[i]->Get());
        }
    }
    void Game::DestroyAll(){
        m_objects.clear();
    }


    std::vector<std::shared_ptr<Object>> Game::CheckCollisions(Object* _obj, std::string _object_type){
        std::vector<std::shared_ptr<Object>> collisions;
        for (size_t i = 0; i<m_objects.size(); i++){
            if(m_objects[i].get()->Type() == _object_type && m_objects[i].get() != _obj){
                if(m_objects[i].get()->GetGlobalBounds().findIntersection(_obj->GetGlobalBounds())){
                    collisions.push_back(m_objects[i]);
                }
            }
        }
        return collisions;
    }
    void Game::CountEnemies(){
        int cnt = 0;
        for (std::shared_ptr<Object> _obj : m_objects){
            if (_obj->Type() == "Enemy" )
                cnt++;
        }
        m_enemy_cnt = cnt;
    }
    const int Game::GetEnemyCount(){
        return m_enemy_cnt;
    }
    void Game::SetState(GameState _state){
        m_state = _state;
    }
} 