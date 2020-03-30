#include "Warrior.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"

Warrior::Warrior(Properties* props) : Character(props) {
	m_JumpTime = JUMP_TIME;
	m_JumpForce = JUMP_FORCE;

	m_IsGrounded = true;
	m_IsJumping = false;

	m_Collider = new Collider();
	m_Collider->SetBuffer(0, 0, 0, 0);

	m_RigidBody = new RigidBody();
	m_RigidBody->SetGravity(3.0f);

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

	Vector2D cam = Camera::GetInstance()->GetPosition();
	SDL_Rect box = m_Collider->Get();
	box.x -= cam.X;
	box.y -= cam.Y;
	SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Warrior::Update(float dt) {

	GetRigidBody()->UnsetForce();
	SetAnimation("idle");

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		GetRigidBody()->ApplyForceX(-10.0f);
		SetAnimation("moveLeft");
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		GetRigidBody()->ApplyForceX(10.0f);
		SetAnimation("moveRight");
	}

	//Jump
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsGrounded) {
		m_IsJumping = true;
		m_IsGrounded = false;
		m_RigidBody->ApplyForceY(-1 * m_JumpForce);
	}

	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_IsJumping && m_JumpTime > 0) {
		m_JumpTime -= dt;
		m_RigidBody->ApplyForceY(-1 * m_JumpForce);
	}
	else {
		m_IsJumping = false;
		m_JumpTime = JUMP_TIME;
	}

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
		m_IsGrounded = true;
		m_Transform->Y = m_LastSafePostion.Y;
	}
	else {
		m_IsGrounded = false;
	}

	m_Origin->X = m_Transform->X + m_Width / 2;
	m_Origin->Y = m_Transform->Y + m_Height / 2;

	m_Animation->Update();
}


void Warrior::Clean() {
	TextureManager::GetInstance()->Drop(m_TextureID);
	m_AnimationMap.clear();
}