#include "Warrior.h"
#include "TextureManager.h"

Warrior::Warrior(Properties* props) : Character(props) {
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 17, 3, 0, 300, false, m_Flip);
}

void Warrior::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt) {
	m_RigidBody->Update(0.3);
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
	m_Animation->Update();
}

void Warrior::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
}