// AStarAlgorithm.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "AStarAlgorithm.h"
#include <iostream>
#include "POINTS.h"
#include <cmath>
#include <vector>

using namespace std;
#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

#ifdef UNICODE

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

#else

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 

#endif

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASTARALGORITHM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASTARALGORITHM));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTARALGORITHM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASTARALGORITHM);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#define XPOINTS 8
#define YPOINTS 8

static Square square[XPOINTS][YPOINTS];
static POINT player;
static POINT EndPoint;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int len = square[0][0].getLen();
    switch (message)
    {
    case WM_CREATE:
        for (int i = 0; i < XPOINTS; i++)
        {
            for (int j = 0; j < YPOINTS; j++)
            {
                square[i][j].setLen(80);
                square[i][j].setX(i);
                square[i][j].setY(j);
            }
        }
        player.x = square[0][0].getX();
        player.y = square[0][0].getY();
        EndPoint.x = player.x;
        EndPoint.y = player.y;
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            for (int i = 0; i < XPOINTS ; i++)
            {
                for (int j = 0; j < YPOINTS ; j++)
                {
                    Rectangle(hdc, square[i][j].getX() * len  - len / 2 + 100, square[i][j].getY() * len - len / 2 + 100,
                        square[i][j].getX() * len + len / 2 + 100, square[i][j].getY() * len + len / 2 + 100);
                }
            }
            Ellipse(hdc, player.x * len - 20 + 100, player.y * len - 20 + 100,
                player.x * len + 20 + 100, player.y * len + 20 + 100);
            Ellipse(hdc, EndPoint.x * len - 20 + 100, EndPoint.y * len - 20 + 100,
                EndPoint.x * len + 20 + 100, EndPoint.y * len + 20 + 100);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        for (int i = 0; i < XPOINTS; i++)
        {
            for (int j = 0; j < YPOINTS; j++)
            {
                if (abs(x - (square[i][j].getX() * len + 100)) <= len / 2
                    && abs(y - (square[i][j].getY() * len + 100)) <= len / 2)
                {
                    EndPoint.x = square[i][j].getX();
                    EndPoint.y = square[i][j].getY();
                }
            }
        }
        POINT move = { player.x, player.y };
        POINT before = { move.x, move.y };
        while (!(move.x == EndPoint.x && move.y == EndPoint.y))
        {
            double minF = -1;
            int minFindexX = -1;
            int minFindexY = -1;
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                        continue;
                    if (move.x + j < 0 || move.x + j >= XPOINTS
                        || move.y + i < 0 || move.y + i >= YPOINTS)
                        continue;

                    if (square[move.x + j][move.y + i].getOpen() == 0)
                    {
                        square[move.x + j][move.y + i].setOpen(1);
                        POINT temp = { move.x + j, move.y + i };

                        double g = 0;
                        int x, y;
                        x = abs(temp.x - player.x);
                        y = abs(temp.y - player.y);
                        if (x > y)
                        {
                            g += sqrt(y * y + y * y);
                            x -= y;
                            g += x;
                        }
                        else if (x < y)
                        {
                            g += sqrt(x * x + x * x);
                            y -= x;
                            g += y;
                        }
                        else
                            g += sqrt(x * x + y * y);
                        square[move.x + j][move.y + i].setG(g);//Gcost

                        double h = 0;
                        x = abs(temp.x - EndPoint.x);
                        y = abs(temp.y - EndPoint.y);
                        if (x > y)
                        {
                            h += sqrt(y * y + y * y);
                            x -= y;
                            h += x;
                        }
                        else if (x < y)
                        {
                            h += sqrt(x * x + x * x);
                            y -= x;
                            h += y;
                        }
                        else
                            h += sqrt(x * x + y * y);
                        square[move.x + j][move.y + i].setH(h);//Hcost

                        square[move.x + j][move.y + i].setF(g + h);
                    }

                    if (minF < 0 || minF > square[move.x + j][move.y + i].getF())
                    {
                        if (before.x != move.x && before.y != move.y)
                        {
                            minF = square[move.x + j][move.y + i].getF();
                            minFindexX = move.x + j;
                            minFindexY = move.y + i;
                        }
                    }
                }
            }
            before.x = move.x;
            before.y = move.y;
            move.x = minFindexX;
            move.y = minFindexY;
            cout << move.x << " " << move.y << endl;
        }
        InvalidateRect(hWnd, NULL, TRUE);
    }
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
