#include "Bullet.h"

Bullet::Bullet() {

	mTimer = Timer::Instance();

	mSpeed = 1500.0f;

	//Bullet Entity
	mTexture = new Texture("bullet.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Rotate(90);
	Reload();
}

Bullet::~Bullet() {

	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Bullet::Fire(Vector2 pos) {

	Pos(pos);
	Active(true);
}

void Bullet::Reload() {

	Active(false);
}

void Bullet::Update() {

	//Bullet direction
	if(Active()) {
	
		Translate(-VEC2_UP * mSpeed * mTimer-> DeltaTime(), local);

		Vector2 pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::Instance()->SCREEN_HEIGHT + OFFSCREEN_BUFFER || pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFFSCREEN_BUFFER) {
		
			Reload();
		}
	}
}

void Bullet::Render() {

	if(Active()) {
	
		mTexture->Render();
	}
}