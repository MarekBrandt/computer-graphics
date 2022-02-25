/******************************************************************
 Grafika komputerowa, œrodowisko MS Windows - program  przyk³adowy
 *****************************************************************/

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

POINT zaba[13];

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
		case 200: MessageBox(okno, "Marek Brandt:\n184590: ", "Autor", MB_OK);
		}
		return 0;
	
	case WM_LBUTTONDOWN: //reakcja na lewy przycisk myszki
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			return 0;
		}

	case WM_PAINT:
		{
		int x = 200;
		int y = 100;
		int width = 300;
		int height = 300;
		int x2 = x + width;
		int y2 = y + height;

		int lwidth = width / 2 * 1;
		int lheight = height / 5 * 4;
		int lx = width / 2 - lwidth / 2 + x;
		int ly = height / 2 - lheight / 2 + y;

		int ax = 200;
		int ay = 400;
		int awidth = 400;
		int aheight = 300;


		POINT punkty1[] = {
			{lx + lwidth / 7 * 0, ly + lheight / 11 * 1},
			{lx + lwidth / 7 * 2, ly + lheight / 11 * 1},
			{lx + lwidth / 7 * 5, ly + lheight / 11 * 5},
			{lx + lwidth / 7 * 5, ly + lheight / 11 * 10},
			{lx + lwidth / 7 * 2, ly + lheight / 11 * 4},
			{lx + lwidth / 7 * 2, ly + lheight / 11 * 10},
			{lx + lwidth / 7 * 1, ly + lheight / 11 * 11},
			{lx + lwidth / 7 * 0, ly + lheight / 11 * 10}
		};
		int lp1 = sizeof(punkty1) / sizeof(POINT);

		POINT punkty2[] = {
			{lx + lwidth / 7 * 5, ly + lheight / 11 * 1},
			{lx + lwidth / 7 * 6, ly + lheight / 11 * 0},
			{lx + lwidth / 7 * 7, ly + lheight / 11 * 1},
			{lx + lwidth / 7 * 7, ly + lheight / 11 * 10},
			{lx + lwidth / 7 * 5, ly + lheight / 11 * 10}
		};
		int lp2 = sizeof(punkty2) / sizeof(POINT);

		zaba[0] = { ax + awidth / 20 * 0, ay + aheight / 18 * 10 };
		zaba[1] = { ax + awidth / 20 * 5, ay + aheight / 18 * 9 };
		zaba[2] = { ax + awidth / 20 * 3, ay + aheight / 18 * 2 };
		zaba[3] = { ax + awidth / 20 * 7, ay + aheight / 18 * 1 };
		zaba[4] = { ax + awidth / 20 * 8, ay + aheight / 18 * 3 };
		zaba[5] = { ax + awidth / 20 * 8, ay + aheight / 18 * 10 };
		zaba[6] = { ax + awidth / 20 * 10, ay + aheight / 18 * 3 };
		zaba[7] = { ax + awidth / 20 * 12, ay + aheight / 18 * 0 };
		zaba[8] = { ax + awidth / 20 * 13, ay + aheight / 18 * 3 };
		zaba[9] = { ax + awidth / 20 * 15, ay + aheight / 18 * 8 };
		zaba[10] = { ax + awidth / 20 * 18, ay + aheight / 18 * 9 };
		zaba[11] = { ax + awidth / 20 * 9, ay + aheight / 18 * 18 };
		zaba[12] = { ax + awidth / 20 * 0, ay + aheight / 18 * 10 };


			PAINTSTRUCT paint;
			HDC kontekst;

			kontekst = BeginPaint(okno, &paint);
		
			// MIEJSCE NA KOD GDI

			HBRUSH pedzle[] = {
				CreateSolidBrush(COLORREF(0x0000ff00)),
				CreateSolidBrush(COLORREF(0x00ff0000)),
				CreateSolidBrush(COLORREF(0x000000ff)),
				CreateSolidBrush(COLORREF(0x00ff00ff)),
				CreateSolidBrush(COLORREF(0x00000000)),
				CreateSolidBrush(COLORREF(0x000ff0ff))
			};

			SelectObject(kontekst, pedzle[0]);
			Pie(kontekst, x, y, x2, y2,  width/1*0 + x, height / 2 * 1 + y, width / 1 * 0 + x,  height/3*2 + y);

			SelectObject(kontekst, pedzle[1]);
			Pie(kontekst, x, y, x2, y2, width / 1 * 0 + x, height / 3 * 2 + y, width / 1 * 1 + x, height / 2 * 1 + y);
			DeleteObject(pedzle[1]);

			SelectObject(kontekst, pedzle[2]);
			Pie(kontekst, x, y, x2, y2, width / 1 * 1 + x, height / 2 * 1 + y, width / 1 * 1 + x, height / 3 * 1 + y);
			DeleteObject(pedzle[2]);

			SelectObject(kontekst, pedzle[3]);
			Pie(kontekst, x, y, x2, y2, width / 1 * 1 + x, height / 3 * 1 + y, width / 1 * 0 + x, height / 2 * 1 + y);


			SelectObject(kontekst, pedzle[4]);
			Polygon(kontekst, punkty1, lp1);


			SelectObject(kontekst, pedzle[5]);
			Polygon(kontekst, punkty2, lp2);

			SelectObject(kontekst, pedzle[0]);
			PolyBezier(kontekst, zaba, 13);

			Ellipse(kontekst, ax + awidth / 20 * 6-20, ay + aheight / 18 * 5-20, ax + awidth / 20 * 6+20, ay + aheight / 18 * 5+20);
			Ellipse(kontekst, ax + awidth / 20 * 11-20, ay + aheight / 18 * 5-20, ax + awidth / 20 * 11+20, ay + aheight / 18 * 5+20);
			Ellipse(kontekst, ax + awidth / 20 * 8-10, ay + aheight / 18 * 8-10, ax + awidth / 20 * 8+10, ay + aheight / 18 * 8+10);

			for (int i = 0; i < 6; i++) {
				DeleteObject(pedzle[i]);
			}

			// utworzenie obiektu umo¿liwiaj¹cego rysowanie przy u¿yciu GDI+
			// (od tego momentu nie mo¿na u¿ywaæ funkcji GDI
			Graphics grafika(kontekst);
			
			// MIEJSCE NA KOD GDI+

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
