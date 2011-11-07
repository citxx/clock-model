#ifndef COLOR_HPP
#define COLOR_HPP

class Color {
    float data[4];

  public:
    Color(float red, float green, float blue, float alpha = 1.0);
    explicit Color(float brightness);
    Color();
    Color(const Color &color);

    const float * getData() const;
};

#endif  // COLOR_HPP
