#pragma once
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

//Border Data Format
struct sLineSegment {
    float sx, sy;
    float ex, ey;
    float radius;
};
//Stores Border Data
extern std::vector<sLineSegment> vectorLines;

class Borders
{
public:
    static void createBorder(float borderScaler);
    static void createPockets(float borderScaler);
};


struct sPocketProperties {
    glm::vec2 position;
    float radius;
};

extern std::vector<sPocketProperties> pocketLocations;

//testing class
class LineWithCircles : public sf::Drawable {
public:
    sf::CircleShape startCircle;
    sf::CircleShape endCircle;
    sf::RectangleShape rectangle;

    LineWithCircles(sLineSegment vectorLine, float scaling) {
        float dx = vectorLine.ex - vectorLine.sx;
        float dy = vectorLine.ey - vectorLine.sy;
        float length = std::sqrt(dx * dx + dy * dy);
        float angle = std::atan2(dy, dx) * 180.0f / 3.14159f;
        // Set up the circles
        startCircle.setRadius(scaling * vectorLine.radius);
        startCircle.setOrigin(scaling * vectorLine.radius, scaling * vectorLine.radius);
        startCircle.setPosition(scaling * vectorLine.sx, scaling * vectorLine.sy);

        endCircle.setRadius(scaling * vectorLine.radius);
        endCircle.setOrigin(scaling * vectorLine.radius, scaling * vectorLine.radius);
        endCircle.setPosition(scaling * vectorLine.ex, scaling * vectorLine.ey);

        // Set up the rectangle
        rectangle.setSize(sf::Vector2f(scaling * length, scaling * 2 * vectorLine.radius));
        rectangle.setOrigin(0, scaling * vectorLine.radius);
        rectangle.setPosition(scaling * vectorLine.sx, scaling * vectorLine.sy);
        rectangle.setRotation(angle);
    }

protected:
    // Override draw function from sf::Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(rectangle, states);
        target.draw(startCircle, states);
        target.draw(endCircle, states);
    }
};