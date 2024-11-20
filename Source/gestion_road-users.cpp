#include "../Headers/main.hpp"
#include "../Headers/classes.hpp"
#include <iostream>


Car::Car(Vertex voie) : voie_(voie){
	type_ = 0;
	n_speed_ = 3;


	Texture texture_voiture;
	texture_voiture.loadFromFile("../../../../Assets/Vehicules/vecteezy_car-top-view-clipart-design-illustration_9380944.png");

	Sprite sprite_voiture(texture_voiture);
	sprite_voiture.setScale((float)0.02, (float)0.02);
	//sprite_voiture.setPosition();			A MODIFIER

	sprite_ = sprite_voiture;

}

int Car::get_type() {
	return type_;
}

float Car::get_n_speed() {
	return n_speed_;
}

Sprite Car::return_sprite() {
	return sprite_;
}