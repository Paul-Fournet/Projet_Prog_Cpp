#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
using namespace sf;

//Couleurs des feux
enum class Traffic_color {
    green = 0,
    orange = 1,
    red = 2
};

Traffic_color operator++(Traffic_color& traffic_color);


class Traffic_light {
private:
    Color color_;
    int type_;//0 : horizontal       1 : vertical
    Vector2f position_;
    std::mutex mtx;//Mutex permettant de sécuriser l'accès au feu de circulation
    CircleShape shape;

public:
    Traffic_light(const sf::Color& color, int type, const Vector2f& position);
    Color get_color();
    void set_color(Color color);
    int get_type();
    void set_type(int type);
    Vector2f get_position();
    void set_position(Vector2f& position);
    Traffic_light operator++();
    std::mutex& get_mutex();
    CircleShape return_traffic_light() const;//Arguments à vérifier
};

void run_traffic_light(Traffic_light& tlHG, Traffic_light& tlHD, Traffic_light& tlVH, Traffic_light& tlVB,float time_on,float time_transition);



class RoadUser {
protected:
    int type_;//0 : voiture, 1 : bus, 2 : piétons, 3 : vélos
    float n_speed_;
    Sprite sprite_;
public:
    virtual int get_type() = 0;
    virtual float get_n_speed() = 0;
    virtual Sprite return_sprite()=0;
};


class Car : RoadUser {
private:
    Vertex voie_;

public:
    Car(Vertex voie);//La voie et la vitesse vont être déterminés automatiquement
    int get_type();
    float get_n_speed();
    Sprite return_sprite();
};