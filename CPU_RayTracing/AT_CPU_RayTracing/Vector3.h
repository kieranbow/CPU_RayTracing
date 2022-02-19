#include <math.h>

constexpr float epsilon = 0.000001f;

// Add template to vector
class Vector3
{
	public:
		Vector3() = default;
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		~Vector3() = default;

		Vector3 operator+(const Vector3& _a)
		{
			Vector3 vector;
			vector.x = this->x + _a.x;
			vector.y = this->y + _a.y;
			vector.z = this->z + _a.z;
			return vector;
		}

		Vector3 operator+(const float& _a)
		{
			Vector3 vector;
			vector.x = this->x + _a;
			vector.y = this->x + _a;
			vector.z = this->x + _a;
			return vector;
		}

		Vector3 operator+=(const Vector3& _a)
		{
			this->x += _a.x;
			this->y += _a.y;
			this->z += _a.z;
			return *this;
		}

		Vector3 operator-(const Vector3& _a)
		{
			Vector3 vector;
			vector.x = this->x - _a.x;
			vector.y = this->y - _a.y;
			vector.z = this->z - _a.z;
			return vector;
		}

		Vector3 operator-=(const Vector3& _a)
		{
			this->x -= _a.x;
			this->y -= _a.y;
			this->z -= _a.z;
			return *this;
		}

		Vector3 operator*(const Vector3& _a)
		{
			Vector3 vector;
			vector.x = this->x * _a.x;
			vector.y = this->y * _a.y;
			vector.z = this->z * _a.z;
			return vector;
		}

		Vector3 operator*=(const Vector3& _a)
		{
			this->x *= _a.x;
			this->y *= _a.y;
			this->z *= _a.z;
			return *this;
		}

		Vector3 operator/(const Vector3& _a)
		{
			Vector3 vector;
			vector.x = this->x / _a.x;
			vector.y = this->y / _a.y;
			vector.z = this->z / _a.z;
			return vector;
		}

		// Produces a new vector C using vector A and B
		static Vector3 cross(const Vector3& _a, const Vector3& _b)
		{
			float x = (_a.y * _b.z) - (_a.z * _b.y);
			float y = (_a.z * _b.x) - (_a.x * _b.z);
			float z = (_a.x * _b.y) - (_a.y * _b.x);
			return Vector3(x, y, z);
		}

		// Calculates the relationship between two vectors. I.e opposite vectors = -1
		static float dot(const Vector3& _a, const Vector3& _b)
		{
			return (_a.x * _b.x) + (_a.y * _b.y) + (_a.z * _b.z);
		}

		// Finds the magnitude from the vectors x,y,z coords
		static float magnitude(const Vector3& _a)
		{
			return sqrtf((_a.x * _a.x) + (_a.y * _a.y) + (_a.z * _a.z));
		}

		// Normalizes a vector using it magnitude
		static Vector3 normalize(const Vector3& _a)
		{
			float mag = magnitude(_a);

			if (mag < epsilon) return Vector3(0.0f, 0.0f, 0.0f);
			return Vector3(_a.x / mag, _a.y / mag, _a.z / mag);
		}

		void setX(float _x)
		{
			x = _x;
		}

		void setY(float _y)
		{
			y = _y;
		}

		void setZ(float _z)
		{
			z = _z;
		}

		// Get the x component by reference
		const float& getX() const
		{
			return x;
		}

		// Get the y component by reference
		const float& getY() const
		{
			return y;
		}

		// Get the z component by reference
		const float& getZ() const
		{
			return z;
		}

	private:
		float x = 0;
		float y = 0;
		float z = 0;
};
