#include<SFML/Graphics.hpp>

using namespace sf;

int main(void) 
{
	RenderWindow app(VideoMode(256, 256), "PuzzleGame");
	app.setFramerateLimit(60);

	Texture t;
	t.loadFromFile("images/15.png");

	int w = 64;	// 퍼즐 하나의 폭

	int grid[6][6] = { 0, };

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
