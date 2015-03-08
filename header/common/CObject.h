#ifndef COBJECT_H
#define COBJECT_H


#include <common/CQuery.h>


class CObject
{
    public :
        inline                  CObject(const int& id) : m_id(id), m_isVisible(true)   {}
        inline virtual  int     update(CQuery& in)                  {return 0;}
        inline const    int&    getId() const                       {return m_id;}
        inline const    bool&   isVisible() const                   {return m_isVisible;}

    protected :
        int     m_id;
        bool    m_isVisible;
};


#endif


