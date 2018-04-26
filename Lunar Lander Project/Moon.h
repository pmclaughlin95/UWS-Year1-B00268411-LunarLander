#ifndef MOON_H
#define MOON_H

class Moon
{
public:
	Moon();
	void show();
	float HeightPos(float x) {
		int index = x * heights / screenWidth;
		return lineHeight[index];

	}
	int flatArea1; 
	int flatArea2; 
	int flatArea3;
 
private:
	const int screenWidth = 800;
	static const int heights = 500;
	float lineHeight[heights];
	float x, y;
	
	
};

#endif 