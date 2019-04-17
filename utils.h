#pragma once
#pragma warning(disable:4996)
#define PI 3.141592f
#define PI2 2 * PI

//프레임 이미지 회전을 위한 각도값
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

class vector2D
{
public:
	double x;
	double y;
	vector2D() {}
	vector2D(double newX, double newY) { x = newX, y = newY; };
	~vector2D() {};
	//외적
	double cross(const vector2D& other) const
	{
		return x * other.y - y * other.x;
	}

	//벡터의 실수배
	vector2D operator * (double r) const
	{
		return vector2D(x*r, y*r);
	}
	//벡터의 덧셈
	vector2D operator + (vector2D other) const
	{
		return vector2D(x + other.x, y + other.y);
	}
	//벡터의 뺄셈
	vector2D operator - (vector2D other) const
	{
		return vector2D(x - other.x, y - other.y);
	}
	//두 벡터의 비교
	bool operator == (vector2D other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator < (vector2D other) const
	{
		return x < other.x && y < other.y;
	}
};

namespace BRAVO_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2);

	float getAngle(float x1, float y1, float x2, float y2);

	inline const string MakeImageName(const char* imageName, const char* folderName = nullptr)
	{
		string str = "";

		if (nullptr != folderName)
		{
			str.append(folderName);
			str.append("/");
		}

		str.append(imageName);
		str.append(".bmp");

		return str;
	}

	inline const string AppendInt(const char* imageName, int value)
	{
		string str = "";
		char num[128];

		itoa(value, num, 10);

		str.append(imageName);
		str.append(num);

		return str;
	}

	//===================================Vector2D====================================


	//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
	inline double ccw(vector2D a, vector2D b)
	{
		return a.cross(b);
	}
	//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계방향이면 음수, 평행이면 0을 반환 한다.
	inline double ccw(vector2D p, vector2D a, vector2D b)
	{
		return ccw(a - p, b - p);
	}

	inline bool lineIntersection(vector2D a, vector2D b, vector2D c, vector2D d, vector2D& x)
	{
		double det = (b - a).cross(d - c);
		//두선이 평행인 경우
		if (fabs(det) < 0.0001f) return false;
		x = a + (b - a)*((c - a).cross(d - c) / det);
		return true;
	}

	//점 a, b와 점 c, d가 평행한 두 선분 일 때 이들이 한 점에서 겹치는지 확인한다.
	inline bool paralleSegments(vector2D a, vector2D b, vector2D c, vector2D d, vector2D& p)
	{
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);

		//한 직선위에 없거나 두 선분이 겹치지 않는 경우를 우선 걸러낸다. 본문의 1번 관계인 경우이다.
		if (ccw(a, b, c) != 0 || b < c || d < a) return false;

		//두 선분이 확실히 겹친다면 교차점 하나를 찾는다.
		if (a < c) p = c;
		else p = a;
		return true;
	}


	// - p가 두 점 a, b를 감싸면서 각 변이 x, y축에 평행한 최소사각형 내부에 있는지 확인한다.
	// a, b, p는 일직선 상에 있다고 가정한다.
	inline bool inBoundingRectangle(vector2D p, vector2D a, vector2D b)
	{
		if (b < a) swap(a, b);
		return p == a || p == b || (a < p && p < b);
	}


	// - 두 점 a, b를 지나는 선분과 두 점 c, b를 지나는 선분을 p에 반환한다.
	// - 교짐이 여러개일 경우 아무점이나 반환한다.
	inline bool segmentIntersection(vector2D a, vector2D b, vector2D c, vector2D d, vector2D& p)
	{
		//두 직선이 평행인 경우를 우선 예외로 처리한다.
		if (!lineIntersection(a, b, c, d, p))
			return paralleSegments(a, b, c, d, p);
		//p가 두 선분에 포함되어 있는 경우에만 참을 반환한다.
		return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
	}

	//두 선분이 서로 접촉하는지 여부를 반환한다.
	inline bool sementIntersects(vector2D a, vector2D b, vector2D c, vector2D d)
	{
		double ab = ccw(a, b, c) * ccw(a, b, d);
		double cd = ccw(c, d, a) * ccw(c, d, b);
		//두 선분이 한 직선에 위에 있거나 끝점이 겹치는 경우
		if (ab == 0 && cd == 0)
		{
			if (b < a) swap(a, b);
			if (d < c) swap(c, d);
			return !(b < c || d < a);
		}
		return ab <= 0 && cd <= 0;
	}

	inline bool rectInIso(vector2D& p, RECT rc)
	{
		vector2D p1, p2, p3;
		p1.x = p.x - 64;
		p1.y = p.y + 32;
		p2.x = p.x;
		p2.y = p.y + 64;
		p3.x = p.x + 64;
		p3.y = p.y + 32;

		vector2D rcP[4];

		rcP[0].x = rc.left;
		rcP[0].y = rc.top;
		rcP[1].x = rc.right;
		rcP[1].y = rc.top;
		rcP[2].x = rc.right;
		rcP[2].y = rc.bottom;
		rcP[3].x = rc.left;
		rcP[3].y = rc.bottom;

		if (sementIntersects(p, p1, rcP[0], rcP[1])
			|| sementIntersects(p, p1, rcP[1], rcP[2])
			|| sementIntersects(p, p1, rcP[2], rcP[3])
			|| sementIntersects(p, p1, rcP[3], rcP[0])
			|| sementIntersects(p1, p2, rcP[0], rcP[1])
			|| sementIntersects(p1, p2, rcP[1], rcP[2])
			|| sementIntersects(p1, p2, rcP[2], rcP[3])
			|| sementIntersects(p1, p2, rcP[3], rcP[0])
			|| sementIntersects(p2, p3, rcP[0], rcP[1])
			|| sementIntersects(p2, p3, rcP[1], rcP[2])
			|| sementIntersects(p2, p3, rcP[2], rcP[3])
			|| sementIntersects(p2, p3, rcP[3], rcP[0])
			|| sementIntersects(p3, p, rcP[0], rcP[1])
			|| sementIntersects(p3, p, rcP[1], rcP[2])
			|| sementIntersects(p3, p, rcP[2], rcP[3])
			|| sementIntersects(p3, p, rcP[3], rcP[0]))
		{
			return true;
		}
		else
			return false;
	}
}
