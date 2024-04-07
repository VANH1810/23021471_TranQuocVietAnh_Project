#pragma once
#include "Config.cpp"
class Vector2D
{
    public:
        float x;
        float y;
        Vector2D();
        Vector2D(float x, float y);

        Vector2D& Add(const Vector2D& vec);
        Vector2D& Subtract(const Vector2D& vec);
        Vector2D& Multiply(const Vector2D& vec);
        Vector2D& Divide(const Vector2D& vec);

        friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
        friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
    
        Vector2D& operator+=(const Vector2D& vec);
        Vector2D& operator-=(const Vector2D& vec);
        Vector2D& operator*=(const Vector2D& vec);
        Vector2D& operator/=(const Vector2D& vec);

        Vector2D& operator*(const float &i);
        Vector2D& Zero();

        friend ostream& operator<<(ostream& os, const Vector2D& vec);

        float length() const
        {
            return sqrt(x * x + y * y);
        }
        void normalize() 
        {
            float len = length();
            if(len != 0)
            {
                x /= len;
                y /= len;
            }
        }
};
