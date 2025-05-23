#pragma once
#include <Enemy.hpp>
#include <Bullet.hpp>
#include <SFML/Graphics.hpp>
#include <Timer.hpp>
#include <Game.hpp>
namespace MyGame{
    int global_flow = 1; // -1 - влево, 1 - вправо
    bool has_shot = false;
    int shot_variant = 0;
    float min_distance = float(game_width);
    void Enemy::SetBaseValues(){
        m_single_cell_x = 3*m_shape.getSize().x/8;
        m_single_cell_y = 5*m_shape.getSize().y/4;
        m_time_passed_since_movement = 0;
        m_base_time_offset = 0.75f;
        m_flow = global_flow;
        m_leftbound = m_shape.getSize().x;
        m_rightbound = game_width * 4.0f/5 + m_shape.getSize().x/2;
        return;
    }

    std::string Enemy::Type(){
        return "Enemy";
    }
    void Enemy::Update(){
        has_shot = false;
        if (shot_variant == 0){
            shot_variant = rand()%2 + 1;
        }
        std::vector<std::shared_ptr<Object>> found = m_game->Find("Ship");
        if (found.size() > 0){
            float dist = std::abs(found[0]->Get().getPosition().x - this->Get().getPosition().x);
            if(dist <= min_distance){
            min_distance = dist;
            closest = this;
            }
        }

        m_time_passed_since_last_shot += Time.Get_Delta_Time();
        if (m_shape.getPosition().y > game_height + m_shape.getSize().y/2){
            m_game->SetState(GameState::Loss);
            m_isAlive = false;
        }
        m_time_passed_since_movement += Time.Get_Delta_Time();
        if(m_flow == global_flow){
            if(m_time_passed_since_movement > m_base_time_offset){
                if (m_shape.getPosition().x + m_flow * m_single_cell_x < m_leftbound || m_shape.getPosition().x + m_flow * m_single_cell_x > m_rightbound){
                    global_flow = -global_flow;
                } 
            }
        }
        // if (m_flow == global_flow){{
        //     if (m_time_passed_since_xmovement > m_base_time_offset){
        //         m_shape.move({global_flow* m_single_cell, 0}); //у меня в спрайтах тут 8 пикселей размер, так что с делением проблем не будет
        //         m_time_passed_since_xmovement = 0;

        //         if (m_shape.getPosition().x > m_rightbound || m_shape.getPosition().x < m_leftbound){
        //             global_flow = -global_flow;
        //         }
        //     }
        //     }
        // }
        // else{
        //     m_flow = global_flow;
        //     if((m_time_passed_since_xmovement <= dt * 1.1) && (m_time_passed_since_ymovement > dt*0.9)){
        //         m_shape.move({m_flow*m_single_cell,0});
        //         m_time_passed_since_xmovement = 0;
        //     }
        //     m_shape.move({0,m_single_cell}); // это будет 10 пикселей вниз
        //     std::cerr << "ts called\n";
        //     m_time_passed_since_ymovement = 0;
        // }
    }

    void Enemy::AfterUpdate(){
        if(m_time_passed_since_movement > m_base_time_offset){
            Animate();
        }
        if(m_time_passed_since_last_shot > m_base_time_offset*2){
            m_time_passed_since_last_shot = 0;
            if(shot_variant == 0){
                min_distance = float(game_width);
                has_shot = false;
            }
            if(!has_shot){
            if(shot_variant == 2){
                if((rand()%std::min(15,m_game->GetEnemyCount()) == std::min(14, m_game->GetEnemyCount()/2))){
                    std::cout << "i spawn\n";
                    has_shot = true;
                    shot_variant = 0;
                    min_distance = float(game_width);
                    Shoot();
                }
            }
            else if(shot_variant == 1){
                std::vector<std::shared_ptr<Object>> found = m_game -> Find("Ship");
                if (found.size()>0){
                    std::cout << min_distance << "\n";
                    if (this == closest){
                        std::cout << min_distance << "\n";
                        std::cout << "i spawn\n";
                        has_shot = true;
                        shot_variant = 0;
                        min_distance = float(game_width);
                        std::cout << min_distance;
                        Shoot();
                    }
                }
            }
            }
        }
        if(global_flow != m_flow){
            m_flow = global_flow;
            m_shape.move({0, m_single_cell_y});
            m_time_passed_since_movement = 0;
            return;
        }
        if (m_time_passed_since_movement > m_base_time_offset){
            m_shape.move({m_flow*m_single_cell_x,0});
            m_time_passed_since_movement = 0;
        }
    }
    void Enemy::Animate(){
        if (++m_curr_frame >= m_animations[m_curr_animation].size())
            m_curr_frame = 0;
        m_shape.setTexture(m_animations[m_curr_animation][m_curr_frame].get());
    }
    void Enemy::Shoot(){
        Bullet* newbul = new Bullet(EnemyBullets[rand()%3]);
        newbul->SetPosition(this->Get().getPosition());
        while(m_game->CheckCollisions(newbul, "Enemy").size() != 0){
            newbul->SetPosition({newbul->Get().getPosition().x, newbul->Get().getPosition().y + enemy_dy});
        }
        m_game->Spawn(newbul);
    }
    Enemy Enemy1 = Enemy("spritesheet.png", 8, 8, 0, 0, 2, 9,0);
    Enemy Enemy2 = Enemy("spritesheet.png", 8, 8, 0, 9, 2, 9,0);
    Enemy Enemy3 = Enemy("spritesheet.png", 8, 8, 0, 18, 2, 9,0);
    Enemy Enemy4 = Enemy("spritesheet.png", 8, 8, 0, 27, 2, 9,0);
    Enemy* closest = nullptr;
}