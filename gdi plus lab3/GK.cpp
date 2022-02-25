/******************************************************************
 Grafika komputerowa, œrodowisko MS Windows - program  przyk³adowy
 *****************************************************************/

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
POINT autko[22];
bool pointClicked = false;
int whichPoint;


//deklaracja funkcji obslugi okna
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//funkcja Main - dla Windows
 int WINAPI WinMain(HINSTANCE hInstance,
               HINSTANCE hPrevInstance,
               LPSTR     lpCmdLine,
               int       nCmdShow)
{
	MSG meldunek;		  //innymi slowy "komunikat"
	WNDCLASS nasza_klasa; //klasa g³ównego okna aplikacji
	HWND okno;
	static char nazwa_klasy[] = "Podstawowa";
	
	GdiplusStartupInput gdiplusParametry;// parametry GDI+; domyœlny konstruktor wype³nia strukturê odpowiednimi wartoœciami
	ULONG_PTR	gdiplusToken;			// tzw. token GDI+; wartoœæ uzyskiwana przy inicjowaniu i przekazywana do funkcji GdiplusShutdown
   
	// Inicjujemy GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusParametry, NULL);

	//Definiujemy klase g³ównego okna aplikacji
	//Okreslamy tu wlasciwosci okna, szczegoly wygladu oraz
	//adres funkcji przetwarzajacej komunikaty
	nasza_klasa.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	nasza_klasa.lpfnWndProc   = WndProc; //adres funkcji realizuj¹cej przetwarzanie meldunków 
 	nasza_klasa.cbClsExtra    = 0 ;
	nasza_klasa.cbWndExtra    = 0 ;
	nasza_klasa.hInstance     = hInstance; //identyfikator procesu przekazany przez MS Windows podczas uruchamiania programu
	nasza_klasa.hIcon         = 0;
	nasza_klasa.hCursor       = LoadCursor(0, IDC_ARROW);
	nasza_klasa.hbrBackground = (HBRUSH) GetStockObject(GRAY_BRUSH);
	nasza_klasa.lpszMenuName  = "Menu" ;
	nasza_klasa.lpszClassName = nazwa_klasy;

    //teraz rejestrujemy klasê okna g³ównego
    RegisterClass (&nasza_klasa);
	
	/*tworzymy okno g³ówne
	okno bêdzie mia³o zmienne rozmiary, listwê z tytu³em, menu systemowym
	i przyciskami do zwijania do ikony i rozwijania na ca³y ekran, po utworzeniu
	bêdzie widoczne na ekranie */
 	okno = CreateWindow(nazwa_klasy, "Grafika komputerowa", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	
	
	/* wybór rozmiaru i usytuowania okna pozostawiamy systemowi MS Windows */
   	ShowWindow (okno, nCmdShow) ;
    
	//odswiezamy zawartosc okna
	UpdateWindow (okno) ;

	// G£ÓWNA PÊTLA PROGRAMU
	while (GetMessage(&meldunek, NULL, 0, 0))
     /* pobranie komunikatu z kolejki; funkcja GetMessage zwraca FALSE tylko dla
	 komunikatu WM_QUIT; dla wszystkich pozosta³ych komunikatów zwraca wartoœæ TRUE */
	{
		TranslateMessage(&meldunek); // wstêpna obróbka komunikatu
		DispatchMessage(&meldunek);  // przekazanie komunikatu w³aœciwemu adresatowi (czyli funkcji obslugujacej odpowiednie okno)
	}

	GdiplusShutdown(gdiplusToken);
	
	return (int)meldunek.wParam;
}

/********************************************************************
FUNKCJA OKNA realizujaca przetwarzanie meldunków kierowanych do okna aplikacji*/
LRESULT CALLBACK WndProc (HWND okno, UINT kod_meldunku, WPARAM wParam, LPARAM lParam)
{
	HMENU mPlik, mInfo, mGlowne;
    	
/* PONI¯SZA INSTRUKCJA DEFINIUJE REAKCJE APLIKACJI NA POSZCZEGÓLNE MELDUNKI */
	switch (kod_meldunku) 
	{
	case WM_CREATE:  //meldunek wysy³any w momencie tworzenia okna
		mPlik = CreateMenu();
		AppendMenu(mPlik, MF_STRING, 100, "&Zapiszcz...");
		AppendMenu(mPlik, MF_SEPARATOR, 0, "");
		AppendMenu(mPlik, MF_STRING, 101, "&Koniec");
		mInfo = CreateMenu();
		AppendMenu(mInfo, MF_STRING, 200, "&Autor...");
		mGlowne = CreateMenu();
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mPlik, "&Plik");
		AppendMenu(mGlowne, MF_POPUP, (UINT_PTR) mInfo, "&Informacja");
		SetMenu(okno, mGlowne);
		DrawMenuBar(okno);

	case WM_COMMAND: //reakcje na wybór opcji z menu
		switch (wParam)
		{
		case 100: if(MessageBox(okno, "Zapiszczeæ?", "Pisk", MB_YESNO) == IDYES)
					MessageBeep(0);
                  break;
		case 101: DestroyWindow(okno); //wysylamy meldunek WM_DESTROY
        		  break;
		case 200: MessageBox(okno, "Imiê i nazwisko:\nNumer indeksu: ", "Autor", MB_OK);
		}
		return 0;
	
	case WM_LBUTTONDOWN: //reakcja na lewy przycisk myszki
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if (!pointClicked) {
			for (int i = 0; i < 22; i++) {
				if ((x - 10 <= autko[i].x) && (x + 10 >= autko[i].x) && (y - 10 <= autko[i].y) && (y + 10 >= autko[i].y)) {
					whichPoint = i;
					pointClicked = true;
				}
			}
		}
		else {
			pointClicked = false;
		}

		return 0;
		}

	case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			if (pointClicked) {
				if (whichPoint == 0 || whichPoint == 21) {
					autko[0].x = autko[21].x = x;
					autko[0].y = autko[21].y = y;
					
				}
				else {
					autko[whichPoint].x = x;
					autko[whichPoint].y = y;
				}
				InvalidateRect(okno, NULL, true);
			}
		}

	case WM_PAINT:
		{
			int x=200;
			int y=100;
			int width=300;
			int height=300;
			int x2 = x + width;
			int y2 = y + height;

			int lwidth=width/4*1;
			int lheight=height/8*5;
			int lx = width/2-lwidth/2+x;
			int ly = height/2-lheight/2+y;

			int ax = 200;
			int ay = 500;
			int awidth = 400;
			int aheight = 100;
			

			POINT punkty1[] = {
				{lx + lwidth/1*0, ly + lheight/1*0},
				{lx + lwidth / 4 * 1, ly + lheight / 1 * 0},
				{lx + lwidth/2*1, ly + lheight/4*1},
				{lx + lwidth/4*3, ly + lheight / 1 * 0},
				{lx + lwidth / 4 * 3, ly + lheight / 2 * 1},
				{lx + lwidth / 2 * 1, ly + lheight / 4 * 3},
				{lx + lwidth / 4 * 1, ly + lheight / 2 * 1},
				{lx + lwidth / 4 * 1, ly + lheight},
				{lx + lwidth / 1 * 0, ly + lheight}
			};
			int lp1 = sizeof(punkty1) / sizeof(POINT);

			POINT punkty2[] = {
				{lx + lwidth / 4 * 3, ly + lheight / 1 * 0},
				{lx + lwidth / 1 * 1, ly + lheight / 1 * 0},
				{lx + lwidth / 1 * 1, ly + lheight / 1 * 1},
				{lx + lwidth / 4 * 3, ly + lheight / 1 * 1},
			};
			int lp2 = sizeof(punkty2) / sizeof(POINT);

			
			autko[0] = { ax + awidth / 26 * 0, ay + aheight / 7 * 3 };
			autko[1] = { ax + awidth / 26 * 5, ay + aheight / 7 * 3 };
			autko[2] = { ax + awidth / 26 * 8, ay + aheight / 7 * 3 };
			autko[3] = { ax + awidth / 26 * 10, ay + aheight / 7 * 0 };
			autko[4] = { ax + awidth / 26 * 11, ay + aheight / 7 * 0 };
			autko[5] = { ax + awidth / 26 * 12, ay + aheight / 7 * 0 };
			autko[6] = { ax + awidth / 26 * 14, ay + aheight / 7 * 0 };
			autko[7] = { ax + awidth / 26 * 16, ay + aheight / 7 * 0 };
			autko[8] = { ax + awidth / 26 * 17, ay + aheight / 7 * 2 };
			autko[9] = { ax + awidth / 26 * 20, ay + aheight / 7 * 2 };
			autko[10] = { ax + awidth / 26 * 22, ay + aheight / 7 * 2 };
			autko[11] = { ax + awidth / 26 * 25, ay + aheight / 7 * 3 };
			autko[12] = { ax + awidth / 26 * 26, ay + aheight / 7 * 5 };
			autko[13] = { ax + awidth / 26 * 22, ay + aheight / 7 * 6 };
			autko[14] = { ax + awidth / 26 * 18, ay + aheight / 7 * 7 };
			autko[15] = { ax + awidth / 26 * 14, ay + aheight / 7 * 7 };
			autko[16] = { ax + awidth / 26 * 10, ay + aheight / 7 * 7 };
			autko[17] = { ax + awidth / 26 * 7, ay + aheight / 7 * 7 };
			autko[18] = { ax + awidth / 26 * 4, ay + aheight / 7 * 7 };
			autko[19] = { ax + awidth / 26 * 0, ay + aheight / 7 * 6 };
			autko[20] = { ax + awidth / 26 * 0, ay + aheight / 7 * 5 };
			autko[21] = { ax + awidth / 26 * 0, ay + aheight / 7 * 3 };
			//int la = sizeof(autko1) / sizeof(POINT);


			/*POINT punkty1[] = {
				{lx + lwidth / 1 * 0, ly + lheight / 1 * 0},
				{lx + lwidth / 6 * 5, ly + lheight / 1 * 0},
				{lx + lwidth / 1 * 1, ly + lheight / 10 * 1},
				{lx + lwidth / 1 * 1, ly + lheight / 10 * 3},
				{lx + lwidth / 6 * 5, ly + lheight / 10 * 4},
				{lx + lwidth / 6 * 2, ly + lheight / 10 * 4},
				{lx + lwidth / 3 * 1, ly + lheight / 1 * 1},
				{lx + lwidth / 1 * 0, ly + lheight / 1 * 1},
				{lx + lwidth / 1 * 0, ly + lheight / 10 * 3},
				{lx + lwidth / 6 * 5, ly + lheight / 10 * 3},
				{lx + lwidth / 6 * 5, ly + lheight / 10 * 1},
				{lx + lwidth / 6 * 1, ly + lheight / 10 * 1},
				{lx + lwidth / 6 * 1, ly + lheight / 10 * 3},
				{lx + lwidth / 1 * 0, ly + lheight / 10 * 3}
			};
			int lp1 = sizeof(punkty1) / sizeof(POINT);

			POINT punkty2[] = {
				{lx + lwidth / 6 * 2, ly + lheight / 10 * 4},
				{lx + lwidth / 6 * 4, ly + lheight / 10 * 4},
				{lx + lwidth / 1 * 1, ly + lheight / 1 * 1},
				{lx + lwidth / 6 * 4, ly + lheight / 1 * 1},
			};
			int lp2 = sizeof(punkty2) / sizeof(POINT);*/

			/*POINT punkty1[] = {
				{lx + lwidth / 4 * 1, ly + lheight / 14 * 4},
				{lx + lwidth / 4 * 3, ly + lheight / 14 * 4},
				{lx + lwidth / 1 * 1, ly + lheight / 14 * 9},
				{lx + lwidth / 4 * 3, ly + lheight / 1 * 1},
				{lx + lwidth / 4 * 1, ly + lheight / 1 * 1},
				{lx + lwidth / 1 * 0, ly + lheight / 14 * 9}
			};
			int lp1 = sizeof(punkty1) / sizeof(POINT);

			POINT punkty2[] = {
				{lx + lwidth / 4 * 1, ly + lheight / 1 * 0},
				{lx + lwidth / 4 * 3, ly + lheight / 1 * 0},
				{lx + lwidth / 1 * 1, ly + lheight / 14 * 1},
				{lx + lwidth / 1 * 1, ly + lheight / 14 * 2},
				{lx + lwidth / 4 * 3, ly + lheight / 14 * 3},
				{lx + lwidth / 4 * 1, ly + lheight / 14 * 3},
				{lx + lwidth / 1 * 0, ly + lheight / 14 * 2},
				{lx + lwidth / 1 * 0, ly + lheight / 14 * 1}
			};
			int lp2 = sizeof(punkty2) / sizeof(POINT);*/

			PAINTSTRUCT paint;
			HDC kontekst;

			kontekst = BeginPaint(okno, &paint);
		
			// MIEJSCE NA KOD GDI

			/*HPEN pioro = CreatePen(PS_SOLID, 10, RGB(255,0,0));
			SelectObject(kontekst, pioro);

			MoveToEx(kontekst, 100, 300, NULL);
			LineTo(kontekst, 800, 300);
			
			DeleteObject(pioro);*/

			HBRUSH pedzle[] = {
				CreateSolidBrush(COLORREF(0x0000ff00)),
				CreateSolidBrush(COLORREF(0x00ff0000)),
				CreateSolidBrush(COLORREF(0x000000ff)),
				CreateSolidBrush(COLORREF(0x00ff00ff)),
				CreateSolidBrush(COLORREF(0x00000000)),
				CreateSolidBrush(COLORREF(0x000ff0ff))
			};
			
			SelectObject(kontekst, pedzle[0]);
			Pie(kontekst, x, y, x2, y2, 0.65*width+x, height+y, 0.2*width+x, 0.2*height+y);

			SelectObject(kontekst, pedzle[1]);
			Pie(kontekst, x, y, x2, y2, 0.2*width+x, 0.2*height+y, 0.5*width+x, height+y);
			DeleteObject(pedzle[1]);

			SelectObject(kontekst, pedzle[2]);
			Pie(kontekst, x, y, x2, y2, 0.5 * width + x,  height + y, 0.6 * width + x, height + y);
			DeleteObject(pedzle[2]);

			SelectObject(kontekst, pedzle[3]);
			Pie(kontekst, x, y, x2, y2, 0.6 * width + x, height + y, 0.65 * width + x, 0*height + y);
			

			SelectObject(kontekst, pedzle[4]);
			Polygon(kontekst, punkty1, lp1);
			

			SelectObject(kontekst, pedzle[5]);
			Polygon(kontekst, punkty2, lp2);
			

			SelectObject(kontekst, pedzle[0]);
			PolyBezier(kontekst, autko, 22);
			

			SelectObject(kontekst, pedzle[1]);
			for (int i = 0; i < 22; i++) {
				Ellipse(kontekst, autko[i].x - 5, autko[i].y - 5, autko[i].x + 5, autko[i].y + 5);
			}
			

			SelectObject(kontekst, pedzle[3]);
			Ellipse(kontekst, ax + awidth / 26 * 6-20, ay + aheight / 7 * 7-20, ax + awidth / 26 * 6+20, ay + aheight / 7 * 7+20);
			Ellipse(kontekst, ax + awidth / 26 * 16-20, ay + aheight / 7 * 7-20, ax + awidth / 26 * 16+20, ay + aheight / 7 * 7+20);
			DeleteObject(pedzle[3]);
			DeleteObject(pedzle[1]);
			DeleteObject(pedzle[0]);
			DeleteObject(pedzle[5]);
			DeleteObject(pedzle[4]);

			// utworzenie obiektu umo¿liwiaj¹cego rysowanie przy u¿yciu GDI+
			// (od tego momentu nie mo¿na u¿ywaæ funkcji GDI
			Graphics grafika(kontekst);
			
			// MIEJSCE NA KOD GDI+


			// utworzenie czcionki i wypisanie tekstu na ekranie
			/*FontFamily  fontFamily(L"Times New Roman");
			Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
			PointF      pointF(100.0f, 400.0f);
			SolidBrush  solidBrush(Color(255, 0, 0, 255));

			grafika.DrawString(L"To jest tekst napisany za pomoc¹ GDI+.", -1, &font, pointF, &solidBrush);*/

			EndPaint(okno, &paint);

			return 0;
		}
  	
	case WM_DESTROY: //obowi¹zkowa obs³uga meldunku o zamkniêciu okna
		PostQuitMessage (0) ;
		return 0;
    
	default: //standardowa obs³uga pozosta³ych meldunków
		return DefWindowProc(okno, kod_meldunku, wParam, lParam);
	}
}
