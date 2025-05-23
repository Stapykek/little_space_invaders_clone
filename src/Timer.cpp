#include <Timer.hpp>
#include <iostream>
#include <SFML/System.hpp>

namespace MyGame{

    float Timer::Get_Delta_Time(){
        return m_dt;
    }
            
    void Timer::Update_Delta_Time(){
        m_dt = m_clock.getElapsedTime().asSeconds();
        m_clock.restart();
    }

    Timer Time;    
}