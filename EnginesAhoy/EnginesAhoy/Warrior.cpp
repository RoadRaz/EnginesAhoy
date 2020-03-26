#include "Warrior.h"
#include "TextureManager.h"
#include "Input.h"

Warrior::Warrior(Properties* props) : Character(props) {
	m_RigidBody = new RigidBody();
	Animation * idleAnimation = new Animation();
	idleAnimation->SetProps(m_TextureID, 0, 17, 3, 0, 100, false, m_Flip);
	AddAnimation("idle", idleAnimation);
	
	Animation* moveLeftAnimation = new Animation();
	moveLeftAnimation->SetProps(m_TextureID, 4, 0, 3, 3, 100, true, m_Flip);
	AddAnimation("moveLeft", moveLeftAnimation);
	
	Animation* moveRightAnimation = new Animation();
	moveRightAnimation->SetProps(m_TextureID, 2, 0, 3, 3, 100, true, m_Flip);
	AddAnimation("moveRight", moveRightAnimation);

	SetAnimation(GetAnimation("idle"));
}

void Warrior::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float dt) {
	m_RigidBody->Update(dt);
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		GetRigidBody()->ApplyForceX(-10.0f);
		SetAnimation("moveLeft");
	}
	else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		GetRigidBody()->ApplyForceX(10.0f);
		SetAnimation("moveRight");
	}
	else {
		GetRigidBody()->UnsetForce();
		SetAnimation("idle");
	}
	m_Transform->TranslateX(m_RigidBody->GetPosition().X);
	//m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();
}


void Warrior::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
	m_AnimationMap.clear();
}