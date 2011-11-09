#include "Color.hpp"

Color::Color(float red, float green, float blue, float alpha) {
    this->data[0] = red;
    this->data[1] = green;
    this->data[2] = blue;
    this->data[3] = alpha;
}

Color::Color(float brightness) {
    this->data[0] = brightness;
    this->data[1] = brightness;
    this->data[2] = brightness;
    this->data[3] = 1.0;
}

Color::Color() {
    this->data[0] = 0.0;
    this->data[1] = 0.0;
    this->data[2] = 0.0;
    this->data[3] = 1.0;
}

Color::Color(const Color &color) {
    this->data[0] = color.data[0];
    this->data[1] = color.data[1];
    this->data[2] = color.data[2];
    this->data[3] = color.data[3];
}

const float * Color::getData() const {
    return this->data;
}
