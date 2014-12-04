//
//  @ Project : PIRATES
//  @ File Name : CWorld.cpp
//  @ Date : 20/10/2014
//  @ Author : Romain
//


#include "CWorldBox.h"



CWorldBox::CWorldBox() :
m_gravity(0.0f, -9.8f),
m_world(m_gravity)
{
  b2BodyDef       groundBodyDef;
  b2PolygonShape  groundBox;
  
  
  groundBodyDef.position.Set(0.0f, -9.8f);
  m_pGroundBody = m_world.CreateBody(&groundBodyDef);
  groundBox.SetAsBox(100.0f, 100.0f);   // Half-width and Half-height
  m_pGroundBody->CreateFixture(&groundBox, 0.0f);
}

CWorldBox::~CWorldBox()
{
  
}

void  CWorldBox::update(sf::Time elapsed)
{
  
}

