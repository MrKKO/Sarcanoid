#include "klocek.h"

klocek::klocek(float pozx, float pozy,bool mm,float width,float hight) {
	shape.setPosition(pozx,pozy);
	motionmode = mm;
	klocekwidth = width;
	klocekhight = hight;
	shape.setSize(Vector2f (width,hight));
	if(mm)shape.setFillColor(Color::Red);
	else { shape.setFillColor(Color::Blue); }
	shape.setOrigin(this->klocekwidth /2.f, this->klocekhight/2.f);
	}

bool klocek::update(float obgryl, float obgryp,float granica) {
	if (this->left() <= 0) { klocekvelocitx *= -1; }
	else if (this->right() >= 800) { klocekvelocitx *= -1; }
	if (obgryl>=0 && obgryp >=800) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 600) {
			klocekvelocitx = basevelo;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 0+granica)) {
			klocekvelocitx = -basevelo;
		}
		else {
			klocekvelocitx = 0;
		}
	}else if(obgryl < 0 && obgryp > 800) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 600) {
			klocekvelocitx = basevelo;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 200)) {
			klocekvelocitx = -basevelo;
		}
		else {
			klocekvelocitx = 0;
		}
	}else if (obgryl <= 0 && obgryp <= 800) {
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && this->right() < 800-granica) {
			klocekvelocitx = basevelo;
		}
		else if ((Keyboard::isKeyPressed(Keyboard::Key::Left) && this->left() > 200)) {
			klocekvelocitx = -basevelo;
		}
		else {
			klocekvelocitx = 0;
		}
	}


	if (Keyboard::isKeyPressed(Keyboard::Key::Up) && this->top() > 280) {
		klocekvelocity = -basevelo;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Down) && this->bottom() < 600-granica) {
		klocekvelocity = basevelo;
	}
	else {
		klocekvelocity = 0;
	}
	tlo = true;
	if (this->klocekvelocitx == 0) { tlo = false; }
	else { tlo = true; }
	shape.move(this->klocekvelocitx, this->klocekvelocity); 
	return tlo;
}


void klocek::draw(RenderTarget& target, RenderStates states)const{
	target.draw(this->shape, states);
	
}

float klocek::left() {
	return this->shape.getPosition().x - this->shape.getSize().x/2.f;
}
float klocek::right() {
	return this->shape.getPosition().x + this->shape.getSize().x/2.f;
}
float klocek::bottom() {
	return this->shape.getPosition().y + this->shape.getSize().y/2.f;
}
float klocek::top() {
	return this->shape.getPosition().y - this->shape.getSize().y/2.f;
}