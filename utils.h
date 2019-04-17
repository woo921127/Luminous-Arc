#pragma once
#pragma warning(disable:4996)
#define PI 3.141592f
#define PI2 2 * PI

//������ �̹��� ȸ���� ���� ������
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
	//����
	double cross(const vector2D& other) const
	{
		return x * other.y - y * other.x;
	}

	//������ �Ǽ���
	vector2D operator * (double r) const
	{
		return vector2D(x*r, y*r);
	}
	//������ ����
	vector2D operator + (vector2D other) const
	{
		return vector2D(x + other.x, y + other.y);
	}
	//������ ����
	vector2D operator - (vector2D other) const
	{
		return vector2D(x - other.x, y - other.y);
	}
	//�� ������ ��
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


	//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	inline double ccw(vector2D a, vector2D b)
	{
		return a.cross(b);
	}
	//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð�����̸� ����, �����̸� 0�� ��ȯ �Ѵ�.
	inline double ccw(vector2D p, vector2D a, vector2D b)
	{
		return ccw(a - p, b - p);
	}

	inline bool lineIntersection(vector2D a, vector2D b, vector2D c, vector2D d, vector2D& x)
	{
		double det = (b - a).cross(d - c);
		//�μ��� ������ ���
		if (fabs(det) < 0.0001f) return false;
		x = a + (b - a)*((c - a).cross(d - c) / det);
		return true;
	}

	//�� a, b�� �� c, d�� ������ �� ���� �� �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
	inline bool paralleSegments(vector2D a, vector2D b, vector2D c, vector2D d, vector2D& p)
	{
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);

		//�� �������� ���ų� �� ������ ��ġ�� �ʴ� ��츦 �켱 �ɷ�����. ������ 1�� ������ ����̴�.
		if (ccw(a, b, c) != 0 || b < c || d < a) return false;

		//�� ������ Ȯ���� ��ģ�ٸ� ������ �ϳ��� ã�´�.
		if (a < c) p = c;
		else p = a;
		return true;
	}


	// - p�� �� �� a, b�� ���θ鼭 �� ���� x, y�࿡ ������ �ּһ簢�� ���ο� �ִ��� Ȯ���Ѵ�.
	// a, b, p�� ������ �� �ִٰ� �����Ѵ�.
	inline bool inBoundingRectangle(vector2D p, vector2D a, vector2D b)
	{
		if (b < a) swap(a, b);
		return p == a || p == b || (a < p && p < b);
	}


	// - �� �� a, b�� ������ ���а� �� �� c, b�� ������ ������ p�� ��ȯ�Ѵ�.
	// - ������ �������� ��� �ƹ����̳� ��ȯ�Ѵ�.
	inline bool segmentIntersection(vector2D a, vector2D b, vector2D c, vector2D d, vector2D& p)
	{
		//�� ������ ������ ��츦 �켱 ���ܷ� ó���Ѵ�.
		if (!lineIntersection(a, b, c, d, p))
			return paralleSegments(a, b, c, d, p);
		//p�� �� ���п� ���ԵǾ� �ִ� ��쿡�� ���� ��ȯ�Ѵ�.
		return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
	}

	//�� ������ ���� �����ϴ��� ���θ� ��ȯ�Ѵ�.
	inline bool sementIntersects(vector2D a, vector2D b, vector2D c, vector2D d)
	{
		double ab = ccw(a, b, c) * ccw(a, b, d);
		double cd = ccw(c, d, a) * ccw(c, d, b);
		//�� ������ �� ������ ���� �ְų� ������ ��ġ�� ���
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
