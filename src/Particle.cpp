#include <Particle.hpp>
#include <Timer.hpp>
namespace MyGame{
    void Particle::Update(){
        m_lifetime -= Time.Get_Delta_Time();
            Animate();
        if (m_lifetime <=0){
            if (m_owner == Owner::Player){
                m_game->SetState(GameState::Loss);
            }
            else if(m_owner == Owner::Enemy){
                if(m_game->GetEnemyCount() == 0){
                    m_game->SetState(GameState::Win);
                }
            }
            m_isAlive = false;
        }
    }
    void Particle::Animate(){
        if (m_animations[m_curr_animation].size()>1){
            m_time_on_frame += Time.Get_Delta_Time();
            if(m_time_on_frame >= m_frame_time){
                m_time_on_frame = 0;
                if (++m_curr_frame >= m_animations[m_curr_animation].size())
                    m_curr_frame = 0;
                m_shape.setTexture(m_animations[m_curr_animation][m_curr_frame].get());
            }
        }
    }
    std::string Particle::Type(){
        switch (m_owner)
        {
        case Owner::Player:
            return "PlayerParticle";
        case Owner::Enemy:
            return "EnemyParticle";
        case Owner::Bullet:
            return "BulletParticle";
        default:
            return "Particle";
        }
    }
    void Particle::SetBaseValues(){
        m_frame_time = 0.1f;
        m_time_on_frame = 0;
    }



    Particle BulletParticle = Particle("spritesheet.png", Owner::Bullet, 0.25f, 8, 8, 116, 45);
    Particle ShipParticle = Particle("spritesheet.png", Owner::Player, 1.f, 15, 8, 130, 63, 2, 17, 0);
    Particle EnemyParticle = Particle("spritesheet.png", Owner::Enemy, 0.25f, 8, 8, 103, 0);
}