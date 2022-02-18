#include <math.h>

constexpr float epsilon = 0.000001f;

class Vector3
{
	public:
		Vector3() = default;
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

		~Vector3() = default;

		Vector3 operator+(const Vector3& a)
		{
			Vector3 vector;
			vector.x = this->x + a.x;
			vector.y = this->y + a.y;
			vector.z = this->z + a.z;
			return vector;
		}

		Vector3 operator-(const Vector3& a)
		{
			Vector3 vector;
			vector.x = this->x - a.x;
			vector.y = this->y - a.y;
			vector.z = this->z - a.z;
			return vector;
		}

		Vector3 operator*(const Vector3& a)
		{
			Vector3 vector;
			vector.x = this->x * a.x;
			vector.y = this->y * a.y;
			vector.z = this->z * a.z;
			return vector;
		}

		Vector3 operator/(const Vector3& a)
		{
			Vector3 vector;
			vector.x = this->x / a.x;
			vector.y = this->y / a.y;
			vector.z = this->z / a.z;
			return vector;
		}

		// Produces a new vector C using vector A and B
		static Vector3 cross(const Vector3& a, const Vector3& b)
		{
			float x = (a.y * b.z) - (a.z * b.y);
			float y = (a.z * b.x) - (a.x * b.z);
			float z = (a.x * b.y) - (a.y * b.x);
			return Vector3(x, y, z);
		}

		// Calculates the relationship between two vectors. I.e opposite vectors = -1
		static float dot(const Vector3& a, const Vector3& b)
		{
			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		// Finds the magnitude from the vectors x,y,z coords
		static float magnitude(const Vector3& a)
		{
			return sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
		}

		// Normalizes a vector using it magnitude
		static Vector3 normalize(const Vector3& a)
		{
			float mag = magnitude(a);

			if (mag < epsilon) return Vector3(0.0f, 0.0f, 0.0f);
			return Vector3(a.x / mag, a.y / mag, a.z / mag);
		}

	private:
		float x = 0;
		float y = 0;
		float z = 0;
};
