#include<SFML/Graphics.hpp>

using namespace sf;

int main(void) 
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame");
	app.setFramerateLimit(60);

	Texture t;
	t.loadFromFile("images/15.png");

	int w = 64;	// 퍼즐 하나의 폭
	int grid[6][6] = { 0, };	// 0은 벽을 의미, 16은 비어있는 공간

	Sprite sprite[17];

	// 초기 이미지 및 타일설정
	int number = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sprite[number].setTexture(t);
			sprite[number].setTextureRect((IntRect(j*w, i*w, w, w))); 
			grid[i + 1][j + 1] = number;
			number++;
		}
	}

	while (app.isOpen()) {	// 창이 열려있는동안
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (e.key.code == Mouse::Left) {
					// 마우스로 누른 위치의 좌표화
					Vector2i pos = Mouse::getPosition(app);
					int x, y;	// grid에 대한 x행 y열
					x = pos.x / 64 + 1;
					y = pos.y / 64 + 1;

					int dx = 0, dy = 0;

					if (grid[y + 1][x] == 16) { dy = 1; dx = 0; }
					else if (grid[y - 1][x] == 16) { dy = -1; dx = 0; }
					else if (grid[y][x + 1] == 16) { dy = 0; dx = 1; }
					else if (grid[y][x - 1] == 16) { dy = 0; dx = -1;}

					// 클릭한 타일과 빈 칸의 위치를 바꿈
					int temp = grid[y][x];
					grid[y][x] = 16;
					grid[y + dy][x + dx] = temp;

					// 애니메이션
					sprite[16].move(-dx * (float)w, -dy * (float)w);
					float speed = 3.f;

					for (int i = 0; i < w; i += (int)speed)
					{
						sprite[temp].move(speed * dx, speed * dy);
						app.draw(sprite[16]);
						app.draw(sprite[temp]);
						app.display();
					}
				}
			}
		}

		app.clear(Color::White);
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int n = grid[i + 1][j + 1];
				sprite[n].setPosition((float)(j * w), (float)(i * w));
				app.draw(sprite[n]);
			}
		}
      app.display();
   }
}
