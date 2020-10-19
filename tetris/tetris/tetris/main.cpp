#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>  
#include <math.h>
#define M 21     //Размер поля игры
#define N 10
#pragma warning(disable: 4996 )
//#pragma comment(linker,"/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //Убираем окно консоли

using namespace sf;


struct Point //Структура координат квадратиков фигуры
{
	int x, y, color; 
};
std::vector<Point> new_fig_rand(); //Функция создания новой фигуры
bool check(std::vector<Point> a, int field[M][N]); //Функция проверки выхода фигуры за границу
void init_text(Text& text, std::string text_in, int cou = -1, bool stop=false); //Функция инициализации текста

float complexity = 0.3; //Сложность игры
bool main_menu = true, isgame = false, isheavu = false, rest = false; //Переменные отображения сцен игры

void game(RenderWindow & window) //Функция цикла игры
{
	int timer_game=0; //Таймер игры
	int offset_horizont=160; //Горизонтальное позиционирование спрайта следующей фигуры
    int offset_vertical = 40; //вертикальное позиционирование спрайта следующей фигуры
	int count_fig = 1;  //Количество выпавших фигур
	int but_gorizontal_offset =240; //Горизонтальное позиционирование кнопок
	int but_vertical_offset = 330; //Вертикальное позиционирование кнопок
	int text_gorizontal_offset = 366; //Горизонтальное позиционирование текста
	int text_vertical_offset = -130; //Вертикальное позиционирование текста
	int text_size = 15; //Размер текста
	int game_points = 0; //Игровые очки
	rest = false; //Рестарт игры
	bool stop = false; //Остановка игры
	int field[M][N] = { 0 }; //Массив поля игры
	int dx = 0; bool rotate = 0; int colorNum = 1; //Вертикальное смещение фигуры, поворот фигуры, номер цвета фигуры
	float timer = 0, delay = complexity; //Таймер для скорости игры, сложность игры
	
    //Инициализация текстур файлами
	Texture texture_tiles, texture_background, texture_frame, texture_exit_on_mouse, texture_exit, texture_menu_on_mouse, texture_menu,
		texture_restart_on_mouse, texture_restart, texture_frame2, texture_frame3;
	texture_background.loadFromFile("images/fon.png");
	texture_frame.loadFromFile("images/fon2.png");
	texture_tiles.loadFromFile("images/tiles.png");
	texture_frame2.loadFromFile("images/frame2.png");
	texture_frame3.loadFromFile("images/frame3.png");
	texture_restart_on_mouse.loadFromFile("images/restart_on_mouse.png");
	texture_restart.loadFromFile("images/restart.png");
	texture_exit_on_mouse.loadFromFile("images/a_mause.png");
	texture_exit.loadFromFile("images/exit_g.png");
	texture_menu_on_mouse.loadFromFile("images/menu_mause.png");
	texture_menu.loadFromFile("images/main_menu_s.png");
	
	//Инициализация спрайтов текстурами
	Sprite but_exit_on_mouse(texture_exit_on_mouse), but_exit(texture_exit), but_menu_on_mouse(texture_menu_on_mouse),
		but_menu(texture_menu), but_rest_on_mouse(texture_restart_on_mouse), but_rest(texture_restart), frame2(texture_frame2), 
		frame3(texture_frame3), tiles(texture_tiles), background(texture_background), frame(texture_frame);
	//Позиционирование спрайтов
	but_exit_on_mouse.setPosition(but_gorizontal_offset-200, but_vertical_offset-50);
	but_exit.setPosition(but_gorizontal_offset-200, but_vertical_offset-50);
	frame2.setPosition(40,10);
	frame3.setPosition(360, 10);
	but_menu_on_mouse.setPosition(but_gorizontal_offset - 200,but_vertical_offset); 
	but_menu.setPosition(but_gorizontal_offset -200, but_vertical_offset);
	but_rest.setPosition(but_gorizontal_offset + 150, but_vertical_offset);
	but_rest_on_mouse.setPosition(but_gorizontal_offset + 150, but_vertical_offset);	
	
	//Инициализация таймера время в игре
	Clock game_time;	
	
	//Инициализация шрифта
	Font font;
	font.loadFromFile("font/AXCCRT.TTF");
	
	//Инициализация и позиционирование текста
	Text Text_next_fig("", font, text_size);
	init_text(Text_next_fig, "Следующая\n фигура");
	Text_next_fig.setPosition(45, 15);
	Text text_time_in_game("", font, text_size);
	text_time_in_game.setPosition(text_gorizontal_offset, text_vertical_offset+150);
	Text text_points_game("", font, text_size);
	text_points_game.setPosition(text_gorizontal_offset+7, text_vertical_offset+250);
	Text text_count_fig("", font, text_size);
	text_count_fig.setPosition(text_gorizontal_offset+7, text_vertical_offset+350);
	Text text_game_over("", font, 25);
	text_game_over.setPosition(100,20);
	init_text(text_game_over, "Игра завершена! ",-1);
	
	std::vector<Point> now_fig(4), temp_fig(4), next_fig(4); //Массив координат актуальной, временной и следующей фигуры
	Clock clock; //Инициализация таймера скорости игры
	Event e; //Событие sfml
	frame.setPosition(0, 0); //Позиционирование главного фона
	
	now_fig = new_fig_rand(); //Генерируем актуальную фигуру
	next_fig = new_fig_rand();//Генерируем следующую фигуру
	
	while (isgame) //Цикл игры
	{
		//Циклически проверяем события
		while (window.pollEvent(e))
		{
			//if (e.type == Event::Closed) window.close(); //Закрываем окно если выход

			if (e.type == Event::KeyPressed)
			{
				//Отслеживание кнопок перемещения по горизонтали
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
			}
		}
		window.clear(Color::White); //Заливаем окно белым цветом
		window.draw(background); //Рисуем фон игры
		window.draw(frame); //Рисуем главную рамку
		if(!stop)window.draw(frame2); //Рисуем рамку  следующей фигуры 
		window.draw(frame3); //Рисуем  рамку статистики
		if (!stop) //если в игре, обновляем время
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;
			window.draw(Text_next_fig);
		  timer_game = std::ceil(game_time.getElapsedTime().asSeconds());
		}
		//Инициализируем игровой текст
		init_text(text_time_in_game, "Время в игре\n", timer_game, stop);
		init_text(text_points_game, "Количество\n очков", game_points, stop);
		init_text(text_count_fig, "Количество\n фигур", count_fig, stop);
		
		window.draw(text_time_in_game); //Рисуем текст таймера
		window.draw(text_points_game); //Рисуем текст игровых очков
		window.draw(text_count_fig); //Рисуем текст количество фигур
		
        //Меняем спрайты кнопок при наведении мыши и отслеживаем нажатия
		if (IntRect(but_gorizontal_offset+150, but_vertical_offset, 80, 40).contains(Mouse::getPosition(window)))
		{ 
			window.draw(but_rest_on_mouse);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				//Если нажата кнопка рестарта 
				isgame = false;
				rest = true;
			}
		}
		else window.draw(but_rest);
		
		if (IntRect(but_gorizontal_offset-200, but_vertical_offset, 80, 40).contains(Mouse::getPosition(window)))
		{
			window.draw(but_menu_on_mouse);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				//Если нажата кнопка главное меню
				main_menu = true;
				isgame = false;
			}
		}
		else window.draw(but_menu);
		
		if (IntRect(but_gorizontal_offset-200, but_vertical_offset-50, 80, 40).contains(Mouse::getPosition(window)))
		{ 
			//Если нажата кнопка выхода
			window.draw(but_exit_on_mouse); 
			
			if (Mouse::isButtonPressed(Mouse::Left)) { isgame = false; window.close(); }
		}
		else window.draw(but_exit);
		
		
		if (Keyboard::isKeyPressed(Keyboard::Down)) //Если нажата кнопка вниз ускоряем фигуру
		{
			delay = 0.05;
		}

		for (int i = 0; i < 4; i++) //Сохраняем предыдущее положение фигуры
		{
			temp_fig[i] = now_fig[i];
			now_fig[i].x += dx;
		}

		if (!check(now_fig, field)) //Если вышла за границы востанавливаем предыдущее положение
		{
			for (int i = 0; i < 4; i++) now_fig[i] = temp_fig[i];
		}

		if (rotate) //Если необходимо повернуть фигуру меняем координаты
		{
			Point p = now_fig[1];
			for (int i = 0; i < 4; i++)
			{
				int x = now_fig[i].y - p.y;
				int y = now_fig[i].x - p.x;
				now_fig[i].x = p.x - x;
				now_fig[i].y = p.y + y;
			}
			if (!check(now_fig, field)) //Если вышла за границу не даем вращать
			{
				for (int i = 0; i < 4; i++) now_fig[i] = temp_fig[i];				
			}
		}
		if (timer > delay) //Если вышло время опускаем фигуру вниз
		{
			for (int i = 0; i < 4; i++)
			{
				temp_fig[i] = now_fig[i];
				now_fig[i].y += 1;
			}

			if (!check(now_fig, field)) //Если фигура достигла дна стакана или других фигур генерируем новую
			{
				//Заносим фигуру в поле игры
				for (int i = 0; i < 4; i++) field[temp_fig[i].y][temp_fig[i].x] = temp_fig[i].color;
				now_fig = next_fig;
				next_fig = new_fig_rand();
				count_fig++;
				if (!check(next_fig, field))
				{
					//Если стакан заполнен останавливаем игру
					stop = true;
				}
			}
			timer = 0; //Обнуляем таймер скорости
		}

		int k = M - 1;
		for (int i = M - 1; i > 0; i--) //Проверяем поле игры на заполненые линии и убираем полные линии
		{
			
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < N) k--;
	
			else game_points += 10;
		}

		dx = 0; rotate = 0; delay = complexity;  //Обнуляем положение, поворот, и скорость падения

        //Рисуем поле игры 
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++) //Обходим масив если не ноль то там квадратик фигуры
										//цифра в масиве это номер цвета
			{
				if (field[i][j] == 0) continue;
				tiles.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				tiles.setPosition(j * 18 + offset_horizont , i * 18 + offset_vertical);
				window.draw(tiles); //Рисуем найденные квадратики
			}
		}

		if (!stop) //Если игра не остановлена выводим спрайт падающей и следующей фигуры
		{
			for (int i = 0; i < 4; i++)
			{
				tiles.setTextureRect(IntRect(next_fig[i].color * 18, 0, 18, 18));
				tiles.setPosition(next_fig[i].x * 18, next_fig[i].y * 18 + 60);
				window.draw(tiles);
				
				tiles.setTextureRect(IntRect(now_fig[i].color * 18, 0, 18, 18));
				tiles.setPosition(now_fig[i].x * 18 + offset_horizont, now_fig[i].y * 18 + offset_vertical);
				window.draw(tiles);
			}
		}
		else
		{
			window.draw(text_game_over); //Если конец игры вывод текст
		}
		window.display();  //Выводим все спрайты на экран
}
}

void menu(RenderWindow & window) //Главное меню
{
	Texture gam, sloz, exit;
	int vertical = 100; // Вертикальное смещение кнопок
	int gorizontal = 150; // Горизонтальное смещение кнопок
	//Инициализация текстур файлами
	gam.loadFromFile("images/game.png");
	sloz.loadFromFile("images/sloznost.png");
	exit.loadFromFile("images/exit.png");
	//Инициализация спрайта текстурами
	Sprite menu1(gam),menu3(sloz), menu4(exit);
	int menu_num=0;
	//Позиционированме спрайтов
		menu1.setPosition(gorizontal, vertical);
		menu3.setPosition(gorizontal, vertical+60);
		menu4.setPosition(gorizontal, vertical+120);

		//Если наведена мышь меняем спрайт и запоминаем кнопку
		if (IntRect(gorizontal, vertical, 200, 50).contains(Mouse::getPosition(window)))
		{
			gam.loadFromFile("images/game2.png");
			menu_num = 1;
		}

		else if (IntRect(gorizontal, vertical + 120, 200, 50).contains(Mouse::getPosition(window)))
		{
			exit.loadFromFile("images/exit_2.png");
			menu_num = 4;
		}

		else if (IntRect(gorizontal, vertical + 60, 200, 50).contains(Mouse::getPosition(window)))
		{
			sloz.loadFromFile("images/sloznost_2.png");
			menu_num = 3;
		}
		//Рисуем кнопки
		window.draw(menu1); 
		window.draw(menu3);
		window.draw(menu4);
	
		if (Mouse::isButtonPressed(Mouse::Left)) //Если нажата мышь активируем нужное меню
		{

			if (menu_num == 3)
			{
				main_menu = false;
				isheavu = true;
				isgame = false;

			}

			if (menu_num == 1)
			{
				main_menu = false;
				isheavu = false;
				isgame = true;
			}
			if (menu_num == 4)
			{
				window.close();
			}
			while (Mouse::isButtonPressed(Mouse::Left)) //Ждем отжатия кнопки
			{

			}
		}
}

void heavu(RenderWindow & window) //Меню выбора сложности
{
		Texture leg, sre, sloznii;
		int menu_num = 0; //Запоминаем номер кнопки
		int vertical = 100; // Вертикальное смещение кнопок
		int gorizontal = 150; // Горизонтальное смещение кнопок
          //Инициализация текстур файлами
		leg.loadFromFile("images/legko.png");
		sre.loadFromFile("images/sredne.png");
		sloznii.loadFromFile("images/tzzelo.png");
		//Инициализация спрайта текстурами
		Sprite menu_sl1(leg), menu_sl2(sre), menu_sl3(sloznii);
		//Позиционированме спрайтов
		menu_sl1.setPosition(gorizontal, vertical);
		menu_sl2.setPosition(gorizontal, vertical+60);
		menu_sl3.setPosition(gorizontal, vertical+120);
		//Если наведена мышь меняем спрайт и запоминаем кнопку
		if (IntRect(gorizontal, vertical, 200, 50).contains(Mouse::getPosition(window)))
		{
			leg.loadFromFile("images/legko_2.png");
			menu_num = 5;
		}

		if (IntRect(gorizontal, vertical+60, 200, 50).contains(Mouse::getPosition(window)))
		{
			sre.loadFromFile("images/sredne_2.png");
			menu_num = 6;
		}

		if (IntRect(gorizontal, vertical+120, 200, 50).contains(Mouse::getPosition(window)))
		{
			sloznii.loadFromFile("images/tzzelo_2.png");
			menu_num = 7;
		}


		if (Mouse::isButtonPressed(Mouse::Left)) //Если нажата мышь активируем нужное меню
		{

			if (menu_num == 5)
			{
				main_menu = false;
				isheavu = false;
				isgame = true;
				complexity = 0.3;
			}

			if (menu_num == 6)
			{
				main_menu = false;
				isheavu = false;
				isgame = true;
				complexity = 0.2;
			}
			if (menu_num == 7)
			{
				main_menu = false;
				isheavu = false;
				isgame = true;
				complexity = 0.1;
			}
		}
		//Рисуем кнопки
		window.draw(menu_sl1);
		window.draw(menu_sl2);
		window.draw(menu_sl3);
	}

bool check(std::vector<Point> a, int field[M][N]) //Функция проверки выхода фигуры за границу
{
	for (int i = 0; i<4; i++)
		if (a[i].x<0 || a[i].x >= N || a[i].y >= M) //Проверяем выход фигуры по горизонтали и вертикали
			return 0;
		else if (field[a[i].y][a[i].x]) //Проверяем совпадение координат с уже существующими фигурами в стакане
			return 0;

		return 1;
};

std::vector<Point> new_fig_rand() //Функция создания новой фигуры
{
	//Массив возможных фигур
	int figure[7][4] =
	{
		1,3,5,7,
		2,4,5,7,
		3,5,4,6,
		3,5,4,7,
		2,3,5,7,
		3,5,7,6,
		2,3,4,5,
	};
	
	std::vector<Point> a(4);
	int n = rand() % 7;
	int colorNum = 1 + rand() % 7; 
	for (int i = 0; i < 4; i++) 
	{	
		a[i].x = figure[n][i] % 2+4; //Преобразуем в массив координат для каждого квадратика
		a[i].y = figure[n][i] / 2;
		a[i].color = colorNum;
	}
	return a;
}

int main()
{
	Texture tex2, game_name; //Главный фон и надпись
    //Инициализация текстур файлами
	tex2.loadFromFile("images/fon.png");
	game_name.loadFromFile("images/game_name.png");
	RenderWindow window(VideoMode(500, 480), "Tetris",Style::Resize); //Создаем окно игры
	//Инициализация спрайта текстурами
	Sprite  background(tex2),sp_game_name(game_name);
	//Позиционированме спрайтов
	sp_game_name.setPosition(40, -40);
	Event e;
	
	while (window.isOpen()) //Главный цикл игры пока открыто окно
	{
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed) window.close(); //Если событие закрытие окна, закрываем окно 
		}	
		window.clear(Color::White); //Заливаем окно белым цветом
		window.draw(background);  //Рисуем главный фон
		window.draw(sp_game_name); //Рисуем картинку названия игры
		if (isgame || rest) //Если входим в игру, либо рестарт игры, активируем функцию начала игры
		{
			isgame = true;
			game(window);
		}					
		if (main_menu ) menu(window);	//Если находимся в главном меню			
		if (isheavu) heavu(window);		//Если в меню выбора сложности	 	
		window.display();  //Выводим на экран
	}
	return 0;
}

void init_text(Text& text, std::string text_in, int cou, bool stop) //Функция инициализации текста
{
	std::ostringstream  stream_text; //Создаем поток для корректного отображения текста и переменных
	if (!stop) text.setColor(Color::White); //Если игра не остановлена, то белый цвет текста
	else text.setColor(Color::Red); //Если игра  остановлена, то красный цвет текста
	text.setStyle(Text::Bold); //Жирный текст
	stream_text << text_in;
	if (cou != -1)
	{
		stream_text << " :"; //Вносим текст в поток
		stream_text << cou;
	}
	text.setString(stream_text.str()); //Выводим с потока в переменную
}
