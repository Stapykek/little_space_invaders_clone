#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Game.hpp>
#include <Object.hpp>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <Block.hpp>
#include <Enemy.hpp>
const float PI = float(acos(-1));
namespace MyGame{
    unsigned int game_width = 224;
    unsigned int game_height = 256;
    float enemy_start_x = 21;
    float enemy_dx = 15;
    float enemy_start_y = 25;
    float enemy_dy = 12;
}
int main(){
    MyGame::LoadBlocks();
    MyGame::Game maingame = MyGame::Game(791, 904, "Space Invaders Clone");
    MyGame::Ship* ship = new MyGame::Ship("spritesheet.png", 13, 8, 113, 63, 3, 17, 0);
    std::vector<std::vector<MyGame::Block*>> Walls;
    int cnt=0;
    
    //здесь создаются стенки
    for (int i = 0; i < 4; i++){
        Walls.push_back({new MyGame::Block(MyGame::left_angle_block), new MyGame::Block(MyGame::basic_block), new MyGame::Block(MyGame::right_angle_block),
            new MyGame::Block(MyGame::basic_block), new MyGame::Block(MyGame::basic_block), new MyGame::Block(MyGame::basic_block),
            new MyGame::Block(MyGame::basic_block), new MyGame::Block(MyGame::little_middle_block), new MyGame::Block(MyGame::basic_block)});
            float block_width = Walls[0][0]->GetSize().x;
        for(int j = 0; j < Walls[i].size(); j++){
            Walls[i][j]->SetPosition({float( 25 + (9*i+1)*block_width/2  + 8*(j%3) ) ,float(180 + 8*(j/3) )});
            maingame.Spawn(Walls[i][j]);
            std::cout << ++cnt << "\n";
        }
    }

    //здесь создаётся кораблик
    maingame.Spawn(ship);

    //здесь создаются враги
    for(int i = 0; i<11;i++){
        std::vector<MyGame::Enemy*> lastrow = {new MyGame::Enemy(MyGame::Enemy3), new MyGame::Enemy(MyGame::Enemy2), new MyGame::Enemy(MyGame::Enemy2), new MyGame::Enemy(MyGame::Enemy1), new MyGame::Enemy(MyGame::Enemy1)};
        for(int j = 0; j<5;j++){
            MyGame::Enemy* lasten = lastrow[j];
            lasten->SetPosition({MyGame::enemy_start_x + MyGame::enemy_dx*i,MyGame::enemy_start_y + MyGame::enemy_dy*j});
            maingame.Spawn(lasten);
        }
    }
    maingame.Run();
    for (int i = 0; i< Walls.size();i++){
        Walls[i].clear();
    }
    std::cout<<"===\nLet's see destructors for all the prefabs\n";
}