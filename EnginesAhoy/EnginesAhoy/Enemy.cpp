#include "Enemy.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "ObjectFactory.h"

static Registrar<Enemy> registrar("enemy");

Enemy::Enemy(Properties* props) : Character(props) {

	m_Collider = new Collider();
	m_Collider->SetBuffer(0, 0, 0, 0);

	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.0f);

	//m_TextureID = "player";

	Animation * idleAnimation = new SpriteAnimation(); //Sprite animation working
	idleAnimation->SetProps(m_TextureID, 0, 17, 3, 0, 100, false);
	AddAnimation("idle", idleAnimation);
	
	Animation* moveLeftAnimation = new SpriteAnimation();
	moveLeftAnimation->SetProps(m_TextureID, 4, 0, 3, 3, 100, true);
	AddAnimation("moveLeft", moveLeftAnimation);
	
	Animation* moveRightAnimation = new SpriteAnimation();
	moveRightAnimation->SetProps(m_TextureID, 2, 0, 3, 3, 100, true);
	AddAnimation("moveRight", moveRightAnimation);

	SetAnimation(GetAnimation("idle"));

	//SequenceAnimation * defaultAnimation = new SequenceAnimation();
	//defaultAnimation->Parse("Assets/animations1.tml");
	//defaultAnimation->SetCurrentSequence("player_idle");
	//AddAnimation("default",defaultAnimation);
	//SetAnimation(GetAnimation("default"));

}

void Enemy::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Enemy::Update(float dt) {

	GetRigidBody()->UnsetForce();
	SetAnimation("idle");

	m_RigidBody->Update(dt);

	m_LastSafePostion.X = m_Transform->X;
	m_Transform->X += m_RigidBody->GetPosition().X;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 26, 32);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->X = m_LastSafePostion.X;
	}

	m_LastSafePostion.Y = m_Transform->Y;
	m_Transform->Y += m_RigidBody->GetPosition().Y;
	m_Collider->Set(m_Transform->X, m_Transform->Y, 26, 32);

	if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
		m_Transform->Y = m_LastSafePostion.Y;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update(dt);
}


void Enemy::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
	m_AnimationMap.clear();
}