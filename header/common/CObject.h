#ifndef COBJECT_H
#define COBJECT_H


#include <common/CQuery.h>


class CObject
{
    public :
        inline                  CMapObject(const int& id) : m_id(id)    {}
        inline virtual  int     update(CQuery& in)                      {return 0;}
        inline const    int&    getId() const                           {return m_id;}

    protected :
        int     m_id;
};


#endif


