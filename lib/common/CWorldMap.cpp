//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include <common/CWorldMap.h>


CWorldMap::CWorldMap() :
m_vObjects()
{

}

CWorldMap::~CWorldMap()
{
  for (std::vector<CMapObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); it++)
    free(*it);
}

int    CWorldMap::update(CMapQuery &in)
{
    int i;

    while (in >> i)
    {
        switch (i)
        {
            case NWorldMap::Add :
            {
                switch(in.nextInt())
                {
                    case NWorldMap::Player :
                        m_vObjects.push_back(new CPlayer(in.nextInt(), in.nextVector2f(), in.nextString()));
                        std::cout << "Ajout du joueur " << ((CPlayer*)m_vObjects.back())->getName() << std::endl;
                        break;
                    default :
                        break;
                }
                break;
            }
            case NWorldMap::Delete :
                m_vObjects.erase(m_vObjects.begin() + in.nextInt());
                break;
            case NWorldMap::Update :
                i = m_vObjects[in.nextInt()]->update(in);
                break;
            default :
                return i;
        }
    }
    return i;
}


