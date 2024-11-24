#include "../Headers/main.hpp"
#include "../Headers/classes.hpp"
#include <iostream>


Car::Car(int voie,Texture& texture,RenderWindow& window) : voie_(voie){
	
	type_ = 0;

	n_speed_ = CAR_SPEED;	
	
	Sprite sprite_voiture(texture);
	sprite_voiture.setScale((float)0.02, (float)0.02);
	//sprite_voiture.setPosition();			A MODIFIER

	if (voie == 1) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C1_X,window.getSize().y * VOIE_C1_Y);
		sprite_voiture.rotate(90);
	}
	if (voie == 2) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C2_X,window.getSize().y* VOIE_C2_Y);
		sprite_voiture.rotate(180);
	}
	if (voie == 3) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C3_X,window.getSize().y * VOIE_C3_Y);
		sprite_voiture.rotate(270);
	}
	if (voie == 4) {
		sprite_voiture.setPosition(window.getSize().x * VOIE_C4_X,window.getSize().y * VOIE_C4_Y);
	}

	sprite_voiture.setOrigin(sprite_voiture.getLocalBounds().width / 2, sprite_voiture.getLocalBounds().height / 2);

	sprite_ = sprite_voiture;

}

int Car::get_type() {
	return type_;
}

int Car::get_voie() {
	return voie_;
}

float Car::get_n_speed() {
	return n_speed_;
}

Sprite& Car::return_sprite() {

	Sprite& ref_sprite = sprite_;

	return ref_sprite;
}



void car_start(Car& car,int delay,RenderWindow& window) {
	
	Clock clock;
	
	window.setActive(false);
	float pos = 0;

	while (window.isOpen()) {

		if (clock.getElapsedTime().asMilliseconds() > delay) {
			clock.restart();

			if (car.get_voie() == 1) {
				car.return_sprite().move(car.get_n_speed(), 0);
			}
			if (car.get_voie() == 2) {
				car.return_sprite().move(0, car.get_n_speed());
			}
			if (car.get_voie() == 3) {
				car.return_sprite().move(-car.get_n_speed(), 0);
			}
			if (car.get_voie() == 4) {
				car.return_sprite().move(0, -car.get_n_speed());
			}
		}
	}
}

