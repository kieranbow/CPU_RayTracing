#include "Vector3.h"

class Ray
{
	public:
		Ray() = default;
		Ray(Vector3 _position, Vector3 _direction) : position(_position), direction(_direction) {}

		~Ray() = default;

		Vector3 position = { 0.0f, 0.0f, 0.0f };
		Vector3 direction = { 0.0f, 0.0f, 0.0f };
		
		void setTvalue(float _value)
		{
			t = _value;
		}

		const Vector3& getPoint()
		{
			return position + Vector3(t, t, t) * direction;
		}

	private:	
		float t = 0;
};
