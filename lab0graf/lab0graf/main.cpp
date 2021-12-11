
#include <math.h>
#include <stdio.h>

// Do³¹cz definicje biblioteki Allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const float FPS = 20;		//obraz bêdzie aktualizowany co 1/FPS sekundy
const int SCREEN_W = 640;	//szerokoœæ okna
const int SCREEN_H = 480;	//wysokoœæ okna

void get_vertexes(float dx[], float dy[], int N, int R) {
	float dfi = 2 * ALLEGRO_PI / N;
	for (int i = 0; i < N; i++) {
		float fi = dfi * i;
		dx[i] = cos(fi) * R;
		dy[i] = sin(fi) * R;
	}
}

// Funkcja g³ówna
int main()
{
	ALLEGRO_DISPLAY *display = NULL;			//okno
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;	//kolejka zdarzen
	ALLEGRO_TIMER *timer = NULL;				//timer, od ktorego bêdziemy odbierac zdarzenia (potrzebny do animacji)
	bool redraw = true;

	if (!al_init()) {							//inicjalizacja biblioteki Allegro
		fprintf(stderr, "Nie zainicjalizowano allegro!\n");
		return -1;
	}
	
	display = al_create_display(SCREEN_W, SCREEN_H);	//utworznie okna
	timer = al_create_timer(1.0 / FPS);					//utworzenie timera
	al_install_keyboard();								//inicjalizacja obs³ugi klawiatury
	event_queue = al_create_event_queue();				//utworzenie kolejki zdarzeñ
	
	al_init_primitives_addon();							//inicjalizacja obs³ugi prostych elementów (punkty, linie, prostok¹ty, elipsy itd.)

	//Rejestracja ¿róde³ zdarzeñ (okno, timer, klawiatura ...)
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	//Kolory rysowania
	ALLEGRO_COLOR yellow = al_map_rgb(255, 255, 0);
	ALLEGRO_COLOR white = al_map_rgba(255, 255, 255, 200);
	ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

	//Definicja wielok¹ta
	const int N = 7;
	const int R = 80;
	/*float dx[N] = { 0.0, -30.0, -10.0, -10.0, 10.0, 10.0, 30.0 };
	float dy[N] = { -60.0, -30.0,-30.0, 60.0, 60.0,-30.0,-30.0 };*/
	float dx[N];
	float dy[N];
	get_vertexes(dx, dy, N, R);

	const int N2 = 3;
	const int R2 = 60;
	float dx2[N2];
	float dy2[N2];
	get_vertexes(dx2, dy2, N2, R2);

	//Tablice na przetworzone wspó³rzêdna punktów
	float points[2*N];
	float points2[2 * N];

	//Zmienne na potrzeby obracania figury
	double fi=0.0, dfi=0.1, sinfi, cosfi, fi2=0.0, sinfi2, cosfi2;

	//Uruchamiamy timer, który bêdzie z zadan¹ czêstotliwoœci¹ wysy³a³ zdarzenia
	al_start_timer(timer);
	
	//Pêtla g³ówna programu - obs³uga zdarzeñ.
	//Dzia³amy, dopóki u¿ytkownik nie wciœnie Esc.
	while(true)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {	//zdarzenie timera -> odœwie¿enie obrazu 
			redraw = true;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {	//zdarzenie klawiatury -> jeœli Esc to koñczymy
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			break;
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //zdarzenie zamkniêcia okna
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) 
		{
			redraw = false;
			al_clear_to_color(black); //czyszczenie okna na zadany kolor

			//Wspolrzedne srodka
			int xm = SCREEN_W / 2;
			int ym = SCREEN_H / 2;
			int xm2 = xm + R + R2;
			int ym2 = ym;

			//Obrót figury
			sinfi = sin(fi);
			cosfi = cos(fi);
			sinfi2 = sin(fi2);
			cosfi2 = cos(fi2);

			xm2 = ((R + R2) * cosfi2 - (0) * sinfi2 + 0.5) + xm;
			ym2 = ((R+R2) * sinfi2 + (0) * cosfi2 + 0.5) + ym;
			for (int i = 0; i < N; i++)
			{
				points[2 * i] = (dx[i] * cosfi - dy[i] * sinfi + 0.5) + xm;
				points[2 * i + 1] = (dx[i] * sinfi + dy[i] * cosfi + 0.5) + ym;
			}
			for (int i = 0; i < N2; i++)
			{
				points2[2 * i] = (dx2[i] * cosfi2 - dy2[i] * sinfi2 + 0.5) + xm2;
				points2[2 * i + 1] = (dx2[i] * sinfi2 + dy2[i] * cosfi2 + 0.5) + ym2;
			}
			fi += dfi;
			fi2 -= dfi;

			//Narysuj wype³niony okr¹g
			//al_draw_filled_circle(xm, ym, 100, blue);
			//al_draw_circle(xm, ym, 100, yellow, 2);

			//Narysuj wype³niony wielokat
			al_draw_polygon(points, N, ALLEGRO_LINE_JOIN_NONE, white, 2, 0);
			al_draw_circle(xm, ym, R, white, 2);

			al_draw_polygon(points2, N2, ALLEGRO_LINE_JOIN_NONE, yellow, 2, 0);
			al_draw_circle(xm2, ym2, R2, yellow, 2);
			
			
			//Wyœwietl w oknie to, co narysowano w buforze
			al_flip_display();
		}
	}

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	return 0;
}
