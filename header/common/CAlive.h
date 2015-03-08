#ifndef CALIVE_H
#define CALIVE_H


class CAlive
{
    public :
        void    update(int hp)
        {
            m_uHp += hp;
            m_bAlive = (m_uHp > 0);
        }

    private :
        unsigned int    m_uHp;
        bool            m_bAlive;
}


#endif


