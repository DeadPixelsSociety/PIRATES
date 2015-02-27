#ifndef CMAPOBJECT_H
#define CMAPOBJECT_H


#include <common/CMapQuery.h>


class CMapObject
{
    public :
        inline  CMapObject(const int& id) : m_id(id)    {}

        inline  virtual int    update(CMapQuery& in)   {return 0;}

        inline  const int&  getId() const    {return m_id;}

    protected :
        int     m_id;
};


#endif


