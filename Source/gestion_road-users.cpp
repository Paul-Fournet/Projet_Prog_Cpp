#include "../Headers/main.hpp"
#include "../Headers/classes.hpp"
#include <iostream>


Car::Car(int voie,Texture& texture,RenderWindow& window) : voie_(voie){
	
	type_ = 0;

	n_speed_ = CAR_SPEED;	
	
	Sprite sprite_voiture(texture);
	sprite_voiture.setScale((float)0.015, (float)0.015);
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
		sprite_voiture.setPosition(window.getSize().x * VOIE_C3_X, window.getSize().y * VOIE_C3_Y);
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

void Car::forward(int delay, float speed,Clock& clock) {

	if (clock.getElapsedTime().asMilliseconds() > delay) {
		clock.restart();

		if (voie_ == 1) {
			sprite_.move(n_speed_, 0);
		}
		if (voie_ == 2) {
			sprite_.move(0, n_speed_);
		}
		if (voie_ == 3) {
			sprite_.move(-n_speed_, 0);
		}
		if (voie_ == 4) {
			sprite_.move(0, -n_speed_);
		}
	}
}



bool isVehicleInRectangle(const sf::Sprite& vehicle_sprite, const sf::RectangleShape& rect) {
	return rect.getGlobalBounds().contains(vehicle_sprite.getPosition());
}


bool can_pass(const sf::Sprite& vehicle_sprite, Traffic_light& feu,RectangleShape& rect) {
	
	if (isVehicleInRectangle(vehicle_sprite, rect) && feu.get_color()==Color::Red) {
		return false;
	}
	else {
		return true;
	}

}



void car_start(Car& car,int delay,RenderWindow& window, vector<Traffic_light*> vect_feux, vector<RectangleShape*> vect_rectangles) {
	
	Clock clock;
	
	window.setActive(false);
	int voie = car.get_voie();
	
	Traffic_light* feu = NULL;
	RectangleShape* rectangle = NULL;

	//On associe à la voiture les feux qu'ils doivent respecter
	if (voie == 1) {
		feu = vect_feux.at(0);
		rectangle = vect_rectangles.at(0);
	}
	if (voie == 2) {
		feu = vect_feux.at(1);
		rectangle = vect_rectangles.at(1);
	}
	if (voie == 3) {
		feu = vect_feux.at(0);
		rectangle = vect_rectangles.at(2);
	}
	if (voie == 4) {
		feu = vect_feux.at(1);
		rectangle = vect_rectangles.at(3);
	}

	if (feu == NULL || rectangle == NULL) {
		return;
	}

	while (window.isOpen()) {

		while (can_pass(std::ref(car.return_sprite()), *feu, *rectangle)) {
			car.forward(delay, car.get_n_speed(), std::ref(clock));
		}

	}
}




