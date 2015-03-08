//
//  @ Project :   PIRATES
//  @ File Name : CWorldMap.cpp
//  @ Date :      12/11/2014
//  @ Author :    Romain
//


#include <common/CWorldMap.h>


int    CWorldMap::update(CQuery &in)
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
                    {
                        int id = in.nextInt();
                        insert(std::pair<int, CPlayer*>(id, new CPlayer(id, in.nextVector2f(), in.nextString())));
                        break;
                    }
                    default :
                        break;
                }
                break;
            }
            case NWorldMap::Delete :
                erase(in.nextInt());
                break;
            case NWorldMap::Update :
                i = at(in.nextInt())->update(in);
                break;
            default :
                return i;
        }
    }
    return i;
}


