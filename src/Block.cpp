#include <Block.hpp>

namespace MyGame{


    void Block::Update(){
        std::vector<std::shared_ptr<Object>> cols = m_game->CheckCollisions(this, "Enemy");
        if (cols.size() > 0)
            m_isAlive = false;
    }
    std::string Block::Type(){
        return "Block";
    }
    
    void Block::GetDamagedFromAbove(){
        m_hits_from_above++;
        if (m_hits_from_above + m_hits_from_below >= m_max_hp){
            std::cout << m_hits_from_above << "and" << m_hits_from_below <<"\n" ;
            m_isAlive = false;
            return;
        }
        else{
            SetFrame(m_hits_from_above);
        }
    }
    void Block::GetDamagedFromBelow(){
        m_hits_from_below++;
        if (m_hits_from_above + m_hits_from_below >= m_max_hp){
            m_isAlive = false;
            return;
        }
        else{
            std::cout << m_hits_from_below << " " << m_hits_from_above << " " << m_animations.size() << "\n";
            SetAnimation(m_hits_from_below , m_hits_from_above);
        }
    }

    Block basic_block = Block("spritesheet.png", 8, 8, 5, 137, 126, 5 , 9, 0);
    Block left_angle_block = Block("spritesheet.png", 8, 8, 3, 182,126, 3,9,0);
    Block right_angle_block = Block("spritesheet.png", 8, 8, 3, 182,153, 3,9,0);
    Block little_middle_block = Block("spritesheet.png", 8, 8, 1, 120,142, 1, 0, 0);
    void LoadBlocks(){
        basic_block.AddAnimation("spritesheet.png", 8, 8, 137, 135, 4, 9, 0);
        basic_block.AddAnimation("spritesheet.png", 8, 8, 137, 144, 3, 9, 0);
        basic_block.AddAnimation("spritesheet.png", 8, 8, 137, 153, 2, 9, 0);
        basic_block.AddAnimation("spritesheet.png", 8, 8, 137, 162, 1, 9, 0);

        left_angle_block.AddAnimation("spritesheet.png", 8, 8, 182, 135, 2, 9, 0);
        left_angle_block.AddAnimation("spritesheet.png", 8, 8, 182, 144, 1, 9, 0);

        right_angle_block.AddAnimation("spritesheet.png", 8, 8, 182, 162, 2, 9, 0);
        right_angle_block.AddAnimation("spritesheet.png", 8, 8, 182, 171, 1, 9, 0);
    }
}
