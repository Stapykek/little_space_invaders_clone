#pragma once
#include <SFML/System.hpp>

namespace MyGame{
    class Timer{
        private:
            sf::Clock m_clock;
            float m_dt;
        public:
            float Get_Delta_Time();

            void Update_Delta_Time();

            Timer(): m_clock(), m_dt(0.0f){}
    };

    extern Timer Time; //спасибо стак оверфлоу
}
