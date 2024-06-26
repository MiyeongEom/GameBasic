// Sample.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Sample.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다 (전방선언)
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


// 윈도우에서 실행되는 프로그램을 만드는 것.
// 윈도우 OS(운영체제) 내부에서 실행되기 시작함.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, /* _In_(데이터가 함수에 입력됐다) 이런거는 SAL 주석이야 그래서 실제적으로 컴파일 시 무시됨.여기에 하나하나 주석을 달기보단 이렇게 함축해 작성하는게 놓은 것*/
                     _In_opt_ HINSTANCE hPrevInstance,   /* _IN_opt_ 의미는 없는데 부가적인 애들이다. -> 그럼 왜 있냐 ? 버전이 올라가면서 메인 함수를 수정을 못한게 아닌가..*/
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)

    // hInstance : 실행된 프로그램(창)의 시작 주소
    // hPrevInstance : 의미 없음
    // lpCmdLine : 프로그램 실행 시 추가 명령어를 넣을 수 있음. 게임 프로그래밍에선 필요 x
    // LPWSTR : 아까 다룬 포인터 ~~ 포인터로 문자 받아오는 것
    // 
{
    UNREFERENCED_PARAMETER(hPrevInstance);  // UNREFERENCED_PARAMETER는 그냥 그 자체로 반환됨
    UNREFERENCED_PARAMETER(lpCmdLine);      // 그래서 의미가 없음. 컴파일러가 삭제함.

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    // 문자열 가져와서 넣어라. 이거 기본 창 만들건데 너가 프로젝트 이름 만든거 넣어줄게 의도. 
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    // 이건 이제 레지스터 정보에 등록
    LoadStringW(hInstance, IDC_SAMPLE, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 위를 기반으로 윈도우 창 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;   // 안만들어지면 종료되도록 하자.
    }

    // 단축키 - 리소스에 AccelTable이 있음. 단축키가 눌리는지 검사. 현재 해보자
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SAMPLE));

    MSG msg;

    // 기본 메시지 루프입니다:
    // 프로그램 내부에 메세지 큐가 있다.
    // 큐 - 먼저 넣는 애들이 먼저 나옴.
    // os입장에선 모든 프로세스를 관리하고 있다.
    // 그래서 여러 메세지가 쌓이게 되는데 현재 포커싱하고 있는 프로세스에 메시지를 넣어준다.
    // 해당 프로세스가 처리하게 도니다.

    // 마우스 드래그 - vs 창과 그림판.
    // 해당 프로그램이 받은 메세지가 있는지 꺼내보자.
    // msg.message;
    // msg.time;
    // msg.hwnd; -> 발생 핸들 (하나의 프로세스에서 여러개의 창 만들기도 가능하기에)
    // 다들어가있기에 주소값으로 접근.

    // 윈도우엔 처리기 함수가 존재한다. 

    while (GetMessage(&msg, nullptr, 0, 0)) 
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키가 눌리는지 검사
        {
            TranslateMessage(&msg);     // 메세지 처리
            DispatchMessage(&msg);      // 너가 처리해.
        }
    }

    // 메세지큐에서 메세지 확인할 때까지 대기함.
    // GetMessage -> true, false 반환, 근데 false 반환되면 종료됨
    // 그래서 false 반환은 msg.message == WM_QUIT인 경우된다 -> 프로그램 종료

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SAMPLE); // 메뉴 - nullptr하면 없어짐
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // 윈도우 운영체제 제공 함수. 내부 구현 볼 수 없음.
    // 그래서 우리가 이젠 만들어 쓰는 것보단 이미 기존에 있는 함수, 만들어놓은 함수가 먼저 있는지 체크한다.
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

   // szTitle 여기에 L"ddd" 이렇게 작성하면 이름 바꿔줌 ~
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
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
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);    /// 메세지가 개많으니 이외의 것은 너가 알아서 처리해라.
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
