//
//  @ Project : PIRATES
//  @ File Name : CWorld.cpp
//  @ Date : 20/10/2014
//  @ Author : Romain
//


#include "CWorld.h"



CWorld::CWorld() :
m_gravity(0.0f, -9.8f),
m_world(gravity)
{
  b2BodyDef       groundBodyDef;
  b2PolygonShape  groundBox;
  
  groundBodyDef.position.Set(0.0f, -9.8f);
  m_pGroundBody = m_world.CreateBody(&groundBodyDef);
  groundBox.SetAsBox(100.0f, 100.0f);   // Half-width and Half-height
  m_PGroundBody->CreateFixture(&groundBox, 0.0f);
}

CWorld::~CWorld()
{
  
}

CWorld::AddDynBody()
{
  b2BodyDef bodyDef;
  
}

