#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Bullet.hpp>
#include <Game.hpp>
#include <Block.hpp>
#include <Timer.hpp>
#include <Enemy.hpp>
#include <Particle.hpp>
namespace MyGame{

    std::string Bullet::Type(){
        if (m_owner == Owner::Player) 
            return "PlayerBullet";
        else if (m_owner>Owner::Player)
            return "EnemyBullet";
        return "Bullet";
    }

    void Bullet::Update(){
        Animate();
        float dt = Time.Get_Delta_Time();
        std::vector<std::shared_ptr<Object>> collisions = m_game->CheckCollisions(this, "Block");
        if (collisions.size() > 0){
            std::cout << "Bullet Collided with " << collisions.size() << " of Blocks\n";
            
            for(int i = 0; i< collisions.size();i++){
                Block* col = dynamic_cast<Block*>(collisions[i].get());
                if (col!= nullptr){
                    if (m_owner==Owner::Player){
                        col->GetDamagedFromBelow();
                    }
                    else if (m_owner==Owner::Enemy){
                        col->GetDamagedFromAbove();
                    }
                }else{
                    std::cout << "it is somehow nullptr.\n";
                }
            }
            m_isAlive = false;
            Particle* newpart = new Particle(BulletParticle);
            newpart->SetPosition(this->Get().getPosition());
            m_game -> Spawn(newpart);
            return;
        }
        if(m_owner == Owner::Player){
            collisions = m_game->CheckCollisions(this, "Enemy");
            if (collisions.size() > 0){
                std::cout << "Bullet Collided with " << collisions.size() << " of Enemies\n";
                for(int i = 0; i< collisions.size();i++){
                    Enemy* col = dynamic_cast<Enemy*>(collisions[i].get());
                    if (col!= nullptr){
                        Particle* newpart = new Particle(EnemyParticle);
                        newpart->SetPosition(col->Get().getPosition());
                        m_game -> Spawn(newpart);
                        col->Kill();    
                    }else{
                        std::cout << "it is somehow nullptr.\n";
                    }
                }
                m_isAlive = false;
                return;
            }
        }
        if(m_owner == Owner::Enemy){
            collisions = m_game->CheckCollisions(this, "Ship");
            if (collisions.size() > 0){
                collisions[0]->Kill();
                Particle* newpart = new Particle(ShipParticle);
                newpart->SetPosition(collisions[0]->Get().getPosition());
                m_game->Spawn(newpart);
                m_isAlive = false;
            }
            
        }
        m_shape.move({0,m_speed*dt});
        if((m_shape.getPosition().y < upperbound) || (m_shape.getPosition().y > lowerbound)){
            Particle* newpart = new Particle(BulletParticle);
            newpart->SetPosition(this->Get().getPosition());
            m_game -> Spawn(newpart);
            m_isAlive = false;
            return; //надо не забывать выходить из функции, если объект деспавнит себя
        }
        
    }
    void Bullet::Animate(){
        if (m_animations[m_curr_animation].size()>1){
            m_time_on_frame += Time.Get_Delta_Time();
            if(m_time_on_frame >= m_frame_changing_frequency){
                m_time_on_frame = 0;
                if (++m_curr_frame >= m_animations[m_curr_animation].size())
                    m_curr_frame = 0;
                m_shape.setTexture(m_animations[m_curr_animation][m_curr_frame].get());
            }
        }
    }
    void Bullet::SetBaseValues(){
        m_frame_changing_frequency = 0.1f; //анимация 10 фпс.
        m_time_on_frame = 0;
        upperbound = 0;
        lowerbound = 320;
    }
    const Bullet PlayerBullet = Bullet("spritesheet.png", -250.0f, Owner::Player, 1,6,120,54);
    const Bullet EnemyBullet1 = Bullet("spritesheet.png", 250.0f, Owner::Enemy, 3,7,112,0,4,9);
    const Bullet EnemyBullet2 = Bullet("spritesheet.png", 250.0f, Owner::Enemy, 3,6,112,9,4,9);
    const Bullet EnemyBullet3 = Bullet("spritesheet.png", 250.0f, Owner::Enemy, 3,6,112,18,4,9);
    const std::vector<Bullet> EnemyBullets = {EnemyBullet1, EnemyBullet2, EnemyBullet3};
}