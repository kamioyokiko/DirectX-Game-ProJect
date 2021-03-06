// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

//배경음
#include<mmsystem.h>
#include <Digitalv.h>

#include"Common.h"
#include"Enemy.h"
#include"Hero.h"
#include"Bullet.h"
#include"BackGround.h"
using namespace std;

// define the screen resolution and keyboard macros
#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 800
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define ENEMY_NUM 7
#define NewENEMY_NUM 2
#define BackNum 2
#define BullLimit 100
#define BossBullLimit 1
#define ENEMY_BullLimit 1


// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

//음악 재생
#pragma comment (lib, "winmm.lib")
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_STATUS_PARMS mciStatus;

// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface
ID3DXFont *font; // 점수
RECT fRectangle;
std::string message;


bool KeyCheck;

int Time;
int counter1_1;
int counter1_2;
int counter1_3;
int Hero_Hit_counter;// 히어로 애니메이션

int Hero_anicounter;// 히어로 애니메이션

int Hero_Hit_anicounter;// 히어로 애니메이션

int CoinBullet_anicounter_1; // 코인총알 애니메이션
int CoinBullet_anicounter_2; // 코인총알 애니메이션
int CoinBullet_anicounter_3; // 코인총알 애니메이션


int EnemyGundam_anicounter; // 일반적 애니메이션
int EnemyGundam_Hit_anicounter; // 일반적 히트 애니메이션


int NewEnemyGundam_anicounter; // 특수적 애니메이션
int NewEnemyGundam_Hit_anicounter; // 특수적 히트 애니메이션


//포물선탄을 위한 변수
float Rand_DroppingBullet;

float score;

// sprite declarations
LPDIRECT3DTEXTURE9 sprite;    // the pointer to the sprite

//플레이어
LPDIRECT3DTEXTURE9 sprite_hero_1;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero_2;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero_3;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_hero_4;    // the pointer to the sprite


LPDIRECT3DTEXTURE9 sprite_Hit_hero_1;    // 플레이어 히트 스프라이트
LPDIRECT3DTEXTURE9 sprite_Hit_hero_2;    // 플레이어 히트 스프라이트


//플레이어 애니메이션
//총알
LPDIRECT3DTEXTURE9 sprite_bullet_1; // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_2;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_3;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_4;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_5;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_6;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_7;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_8;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_9;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_bullet_10;    // the pointer to the sprite // 코인 불렛
LPDIRECT3DTEXTURE9 sprite_superbullet; // 필살기


//적
LPDIRECT3DTEXTURE9 sprite_enemy_1;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_2;    // the pointer to the sprite

LPDIRECT3DTEXTURE9 sprite_enemybullet;

LPDIRECT3DTEXTURE9 sprite_Newenemy_1;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_Newenemy_2;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_Newenemy_3;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_Newenemy_4;    // the pointer to the sprite

LPDIRECT3DTEXTURE9 sprite_Newenemymissile;    // 특수적 호밍미사일

LPDIRECT3DTEXTURE9 sprite_MushroomEnemy; // 버섯


LPDIRECT3DTEXTURE9 sprite_Boss; // 최종보스
LPDIRECT3DTEXTURE9 sprite_BossMissile; // 최종보스

////////////////////////////////////////////////////////////
//적들 피격시 파괴되는 애니메이션
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_1;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_2;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_3;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_4;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_5;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_6;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_7;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_8;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_9;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_10;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_11;    // the pointer to the sprite
LPDIRECT3DTEXTURE9 sprite_enemy_Hit_12;    // the pointer to the sprite



//////////////////////////////////////////////////////////
//백그라운드
//타이틀
LPDIRECT3DTEXTURE9 sprite_Title;    // 타이틀

//인게임 배경화면
LPDIRECT3DTEXTURE9 sprite_BackGround1;    // 배경화면
LPDIRECT3DTEXTURE9 sprite_BackGround2;    // 배경화면

//게임 오버
LPDIRECT3DTEXTURE9 sprite_over;    // 게임오버


//스코어
LPDIRECT3DTEXTURE9 sprite_SThou;
LPDIRECT3DTEXTURE9 sprite_SOne;
LPDIRECT3DTEXTURE9 sprite_SHund;
LPDIRECT3DTEXTURE9 sprite_STen;
LPDIRECT3DTEXTURE9 sprite_ScoreBox;

bool Title; // 타이틀
bool InGame; // 인게임
bool Game_over; // 게임오버

// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);		// closes Direct3D and releases memory
void Score_Manager(void);
void BossAttack(void);

void init_game(void);
void do_game_logic(void);
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);
//bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1);


// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

using namespace std;


enum { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };


//객체 생성
Hero hero;
//Bullet bullet
Bullet bull[BullLimit];
Bullet2 bull2[BullLimit];
Bullet3 bull3[BullLimit];

Enemy enemy[ENEMY_NUM];

EnemyBullet Ebullet[ENEMY_NUM];

NewEnemy newenemy[NewENEMY_NUM];

NewEnemyBullet newenemybull[NewENEMY_NUM];

Mushroom mushroom; // 통과불가 오브젝트

BossEnemy Boss; // 보스

BossBullet1 Bossbull1[BossBullLimit];
BossBullet2 Bossbull2[BossBullLimit];
BossBullet3 Bossbull3[BossBullLimit];
BossBullet4 Bossbull4[BossBullLimit];

BackGround back[2];

//Bullet bullet;
//SuperBullet Superbullet;
//EnemyBullet enemybullet;

//음악재생 관련
UINT wDeviceID = 0;
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
{
	DWORD Result;
	mciOpen.lpstrDeviceType = L"MPEGVideo";
	//재생타입

	mciOpen.lpstrElementName = lpszWave;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	if (Result)
	{
		return Result;
	}

	wDeviceID = mciOpen.wDeviceID;
	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)	
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindow(L"WindowClass", L"DirectX Shooting Game",
		WS_OVERLAPPEDWINDOW, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);


	//게임 오브젝트 초기화 
	init_game();

	// enter the main loop:

	MSG msg;

	DWORD Sound1, Sound2, Sound3;
	Sound1 = LoadWAV(hWnd, L"Yowamushi Pedal OST - Sakamichi.mp3");
	Sound2 = LoadWAV(hWnd, L"Family.mp3");
	Sound3 = LoadWAV(hWnd, L"MarioCoin.mp3");
	//Sound1 = mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);


	while (TRUE)
	{
		DWORD starting_point = GetTickCount();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		do_game_logic();
		render_frame();
		
		// check the 'escape' key
		if (KEY_DOWN(VK_ESCAPE))
			PostMessage(hWnd, WM_DESTROY, 0, 0);

		while ((GetTickCount() - starting_point) < 25);
	}
	// clean up DirectX and COM
	cleanD3D();

	return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
	//화면 전환을 위한 선언
	Title = true;
	InGame = false;
	Game_over = false;


	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	D3DXCreateSprite(d3ddev, &d3dspt);    // create the Direct3D Sprite object

	//타이틀
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Sonic_Title.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Title);    // load to sprite

	//인게임
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"sonic_sprite_background_1.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_BackGround1);    // load to sprite

	//인게임
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"sonic_sprite_background_2.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_BackGround2);    // load to sprite


	 //게임오버
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Sonic_GameOver.png",    // the file name
		1240,    // default width
		800,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_over);    // load to sprite

	///////////////////////////////////////////////////////////////////
	//인게임

	//플레이어
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero/SonicSprite5.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_1);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero/SonicSprite6.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_2);    // load to sprite


	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero/SonicSprite7.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero/SonicSprite8.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_hero_4);    // load to sprite

	//플레이어 히트 스프라이트
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero/SonicHitSprite2.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Hit_hero_1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Hero/SonicHitSprite2.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Hit_hero_2);    // load to sprite



    //플레이어 총알(플레이어가 쓰는 모든 총알)
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite1.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_1);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite2.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_2);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite3.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_3);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite4.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_4);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite5.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_5);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite6.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_6);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite7.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_7);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite8.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_8);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite9.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_9);    // load to sprite

		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"CoinBullet/CoinBulletsprite10.png",    // the file name
			40,    // default width
			40,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_bullet_10);    // load to sprite

	//필살기
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Boss.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_superbullet);    // load to sprite


	//적
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/EnemyGundamSprite1.png",    // the file name
		60,    // default width
		90,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_1);    // load to sprite

	
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/EnemyGundamSprite2.png",    // the file name
		60,    // default width
		90,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_2);    // load to sprite



	//적총알
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"EnemyBullet.png",    // the file name
		D3DX_DEFAULT,    // default width
		D3DX_DEFAULT,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemybullet);    // load to sprite

	/////////////////////////////////////////////////////////////
	//새로운적
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/NewEnemySprite1.png",    // the file name
		100,    // default width
		95,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Newenemy_1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/NewEnemySprite2.png",    // the file name
		100,    // default width
		95,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Newenemy_2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/NewEnemySprite3.png",    // the file name
		100,    // default width
		95,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Newenemy_3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/NewEnemySprite4.png",    // the file name
		100,    // default width
		95,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Newenemy_4);    // load to sprite

	/////////////////////////////////////////////////////////////
	//특수적 호밍총알
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/NewEnemyMissile.png",    // the file name
		60,    // default width
		60,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Newenemymissile);    // load to sprite


	/////////////////////////////////////////////////////////////
	//버섯
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/EnemyMushroom.png",    // the file name
		300,    // default width
		300,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_MushroomEnemy);    // load to sprite


	////////////////////////////////////////////////////////////////
	//보스
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/BossEnemySprite.png",    // the file name
		400,    // default width
		300,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_Boss);    // load to sprite

	  ////////////////////////////////////////////////////////////////
	  //보스 미사일
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/BossEnemyMissile.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_BossMissile);    // load to sprite

	///////////////////////////////////////////////////////////////
	//적들 피격시 파괴 애니메이션
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite1.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_1);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite2.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_2);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite3.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_3);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite4.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_4);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite5.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_5);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite6.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_6);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite7.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_7);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite8.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_8);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite9.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_9);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite10.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_10);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite11.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_11);    // load to sprite

	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Enemy/ExplosionSprite12.png",    // the file name
		40,    // default width
		40,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_enemy_Hit_12);    // load to sprite

	////////////////////////////////////////////////////////////////////
	//스코어박스
	D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
		L"Score/ScoreBox.png",    // the file name
		128,  // default width
		64,    // default height
		D3DX_DEFAULT,    // no mip mapping
		NULL,    // regular usage
		D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
		D3DPOOL_MANAGED,    // typical memory handling
		D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,    // no mip filtering
		D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
		NULL,    // no image info struct
		NULL,    // not using 256 colors
		&sprite_ScoreBox);    // load to sprite

	/*
	font = NULL;
	HRESULT hr = D3DXCreateFont(d3ddev, 40, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FF_DONTCARE, L"Arial", &font);
	if (!SUCCEEDED(hr))

	{
		return;
	}

	SetRect(&fRectangle, 0, 0, 300, 200);
	message = "Shooting Game";
	*/
	return;
}


//충돌
bool sphere_collision_check(float x0, float y0, float size0, float x1, float y1, float size1)
{

	if ((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1) < (size0 + size1) * (size0 + size1))
		return true;
	else
		return false;

}



//적과의 충돌
bool Hero::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		Hero_hit = true;
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}


//적 충돌
bool Enemy::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}


bool NewEnemy::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		bShow = false;
		return true;

	}
	else {
		return false;
	}
}


//총알 발사시 적과의 충돌
bool Bullet::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos-60, y_pos-20, 40, x, y, 40) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}

//아래쪽
bool Bullet2::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos-60, y_pos+20, 40, x, y, 40) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}

//위쪽
bool Bullet3::check_collision(float x, float y)
{

	//충돌 처리 시 
	if (sphere_collision_check(x_pos-60, y_pos-40, 40, x, y, 40) == true)
	{
		bShow = false;
		return true;

	}
	else {

		return false;
	}
}


//적의 총알	발사시 캐릭터와의 충돌
bool EnemyBullet::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 30, x, y, 30) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}

bool NewEnemyBullet::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 10, x, y, 10) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}


bool Mushroom::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos+80, y_pos+110, 80, x, y, 80) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}



bool BossEnemy::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos+50, y_pos+110, 400, x, y, 300) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}

bool BossBullet1::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 20, x, y, 20) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}

bool BossBullet2::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 20, x, y, 20) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}

bool BossBullet3::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 20, x, y, 20) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}

bool BossBullet4::check_collision(float x, float y)
{
	if (sphere_collision_check(x_pos, y_pos, 20, x, y, 20) == true)
	{
		bShow = false;
		return true;
	}
	else
		return false;
}


void init_game(void)
{
	//배경화면 초기화
	back[0].init(0, 0);
	back[1].init(SCREEN_WIDTH, 0);


	//플레이어 초기화 
	hero.init(50, 300);

	//////////////////////////////////////////////////////////////////////////
	//총알 초기화 발사체 갯수 100개 -> BullLimit 만큼으로 변경
	for (int i = 0; i < BullLimit; i++)
	{
		bull[i].init(hero.x_pos, hero.y_pos);
	}


	for (int i = 0; i < BullLimit; i++)
	{
		bull2[i].init(hero.x_pos, hero.y_pos);
	}

	for (int i = 0; i < BullLimit; i++)
	{
		bull3[i].init(hero.x_pos, hero.y_pos);
	}


	///////////////////////////////////////////////////////////////////////////
	//적 초기화 
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT-50);
		
	}

	////////////////////////////////////////////
	//적 총알 초기화
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		Ebullet[i].init(enemy[i].x_pos, enemy[i	].y_pos);
	}



	//새로운적 초기화
	for (int i = 0; i < NewENEMY_NUM; i++)
	{
		newenemy[i].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);

	}


	for (int i = 0; i < NewENEMY_NUM; i++)
	{
		newenemybull[i].init(newenemy[i].x_pos, newenemy[i].y_pos);

	}

	//Superbullet.init(hero.x_pos, hero.y_pos);	
		
	mushroom.init((float)(SCREEN_WIDTH + (rand() % 400)), rand() % SCREEN_HEIGHT - 100);

	Boss.init(2000, 350);

	for (int i = 0; i < BossBullLimit; i++)
	{
		Bossbull1[i].init(Boss.x_pos, Boss.y_pos);
	}

	for (int i = 0; i < BossBullLimit; i++)
	{
		Bossbull2[i].init(Boss.x_pos, Boss.y_pos);
	}

	for (int i = 0; i < BossBullLimit; i++)
	{
		Bossbull3[i].init(Boss.x_pos, Boss.y_pos);
	}

	for (int i = 0; i < BossBullLimit; i++)
	{
		Bossbull4[i].init(Boss.x_pos, Boss.y_pos);
	}

}

void do_game_logic(void)
{
	if (InGame == true)
	{
		Rand_DroppingBullet = (float)((float)((float)(rand() % 10) / 10) + 0.1); // 포물선 탄 변수
		//배경화면 처리
		for (int i = 0; i < BackNum; i++)
		{
			back[i].Move();
		}
		//주인공 처리 
		if (KEY_DOWN(VK_UP))
		{
			hero.move(MOVE_UP);
			if (hero.y_pos < 0)
			{
				hero.y_pos = 0;
			}
		}

		if (KEY_DOWN(VK_DOWN))
		{
			hero.move(MOVE_DOWN);
			if (hero.y_pos > SCREEN_HEIGHT - 60)
			{
				hero.y_pos = SCREEN_HEIGHT - 60;
			}
		}

		if (KEY_DOWN(VK_LEFT))
		{
			hero.move(MOVE_LEFT);
			if (hero.x_pos < 0)
			{
				hero.x_pos = 0;
			}
		}

		if (KEY_DOWN(VK_RIGHT))
		{
			hero.move(MOVE_RIGHT);
			if (hero.x_pos > SCREEN_WIDTH - 60)
			{
				hero.x_pos = SCREEN_WIDTH - 60;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////
		//총알 연사처리(첫번째)
		if (KEY_DOWN(VK_SPACE) && 0x80000)
		{
			mciSendCommand(3, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
			counter1_1++;
			if (counter1_1 % 5 == 0)
			{
				for (int i = 0; i < 100; i++)
				{
					if (bull[i].show() == false)
					{
						bull[i].active();
						bull[i].init(hero.x_pos, hero.y_pos);
						//bull[i].move();
						break;
					}
				}
			}
		}

		else if (KEY_UP(VK_SPACE))
		{
			mciSendCommand(3, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		}

		//총알처리
		for (int i = 0; i < BullLimit; i++)
		{
			if (bull[i].show() == true)
			{
				if (bull[i].x_pos > SCREEN_WIDTH)
					bull[i].hide();
				else
					bull[i].move();

				//일반 적 충돌 처리 
				for (int j = 0; j < ENEMY_NUM; j++)
				{
					if (bull[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true)
					{
						if (Boss.Boss_Exist == false)
						{
							score += 3;
						}
						enemy[j].Enemy_Hit = true;
						if (enemy[j].Enemy_Hit == false)
						{
							enemy[j].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
						}
					}
				}

				//새로운 적 충돌 처리
				for (int t = 0; t < NewENEMY_NUM; t++)
				{
					if (bull[i].check_collision(newenemy[t].x_pos, newenemy[t].y_pos) == true)
					{
						newenemy[t].HP -= 1;
						if (newenemy[t].HP <= 0)
						{
							if (Boss.Boss_Exist == false)
							{
								score += 5;
							}
							newenemy[t].NewEnemy_Hit = true;
							//이후 생성 안되는 버그 해결
							newenemy[t].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
							newenemy[t].HP = 10;
						}
					}
				}

				//호밍미사일이 플레이어 미사일과 충돌시
				for (int k = 0; k < NewENEMY_NUM; k++)
				{
					if (bull[i].check_collision(newenemybull[k].x_pos, newenemybull[k].y_pos) == true)
					{
						newenemybull[k].HP -= 1;
						if (newenemybull[k].HP <= 0)
						{
							newenemybull[k].hide();
						}
					}
				}
				if (bull[i].check_collision(mushroom.x_pos, mushroom.y_pos + 115) == true)
				{
					bull[i].hide();
				}

				if (bull[i].check_collision(Boss.x_pos, Boss.y_pos + 115) == true)
				{
					Boss.HP -= 1;
					if (Boss.HP <= 0)
					{
						Boss.BossEnemy_Hit = true;
						Boss.hide();
					}
				}
			}
		}
		////////////////////////////////////////////////////////////////////////
		//총알 처리 두번째
		if (KEY_DOWN(VK_SPACE) && 0x80000)
		{
			mciSendCommand(3, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
			counter1_2++;
			if (counter1_2 % 5 == 0)
			{
				for (int i = 0; i < 100; i++)
				{
					if (bull2[i].show() == false)
					{
						bull2[i].active();

						bull2[i].init(hero.x_pos, hero.y_pos);
						//bull[i].move();
						break;
					}

				}
			}
		}
		//총알처리
		for (int i = 0; i < BullLimit; i++)
		{
			if (bull2[i].show() == true)
			{
				if (bull2[i].x_pos > SCREEN_WIDTH || bull2[i].y_pos > (SCREEN_HEIGHT + 15))
					bull2[i].hide();
				else
					bull2[i].move();

				//일반 적 충돌 처리 
				for (int j = 0; j < ENEMY_NUM; j++)
				{
					if (bull2[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true)
					{
						if (Boss.Boss_Exist == false)
						{
							score += 3;
						}
						enemy[j].Enemy_Hit = true;

						if (enemy[j].Enemy_Hit == false)
						{
							enemy[j].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
						}
					}
				}

				//새로운 적 충돌 처리
				for (int t = 0; t < NewENEMY_NUM; t++)
				{
					if (bull2[i].check_collision(newenemy[t].x_pos, newenemy[t].y_pos) == true)
					{
						newenemy[t].HP -= 1;
						if (newenemy[t].HP <= 0)
						{
							if (Boss.Boss_Exist == false)
							{
								score += 5;
							}
							newenemy[t].NewEnemy_Hit = true;
							//이후 생성 안되는 버그 해결
							newenemy[t].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
							newenemy[i].HP = 10;
						}
					}
				}

				//호밍미사일이 플레이어 미사일과 충돌시
				for (int k = 0; k < NewENEMY_NUM; k++)
				{
					if (bull2[i].check_collision(newenemybull[k].x_pos, newenemybull[k].y_pos) == true)
					{
						newenemybull[k].HP -= 1;
						if (newenemybull[k].HP <= 0)
						{
							newenemybull[k].hide();
						}
					}
				}

				if (bull2[i].check_collision(mushroom.x_pos, mushroom.y_pos + 160) == true)
				{
					bull2[i].hide();
				}

				if (bull2[i].check_collision(Boss.x_pos, Boss.y_pos + 160) == true)
				{
					Boss.HP -= 1;
					if (Boss.HP <= 0)
					{
						Boss.hide();
					}
				}
			}
		}


		////////////////////////////////////////////////////////////////////////
		//총알 처리 세번째
		if (KEY_DOWN(VK_SPACE) && 0x80000)
		{
			mciSendCommand(3, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
			counter1_3++;
			if (counter1_3 % 5 == 0)
			{
				for (int i = 0; i < 100; i++)
				{
					if (bull3[i].show() == false)
					{
						bull3[i].active();

						bull3[i].init(hero.x_pos, hero.y_pos);
						//bull[i].move();
						break;
					}

				}
			}
		}
		//총알처리
		for (int i = 0; i < BullLimit; i++)
		{
			if (bull3[i].show() == true)
			{
				if (bull3[i].x_pos > SCREEN_WIDTH || bull3[i].y_pos < -50)
					bull3[i].hide();
				else
					bull3[i].move();

				//일반 적 충돌 처리 
				for (int j = 0; j < ENEMY_NUM; j++)
				{
					if (bull3[i].check_collision(enemy[j].x_pos, enemy[j].y_pos) == true)
					{
						if (Boss.Boss_Exist == false)
						{
							score += 3;
						}
						enemy[j].Enemy_Hit = true;
						if (enemy[j].Enemy_Hit == false)
						{
							enemy[j].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
						}
					}
				}

				//새로운 적 충돌 처리
				for (int t = 0; t < NewENEMY_NUM; t++)
				{
					if (bull3[i].check_collision(newenemy[t].x_pos, newenemy[t].y_pos) == true)
					{
						newenemy[t].HP -= 1;
						if (newenemy[t].HP <= 0)
						{
							if (Boss.Boss_Exist == false)
							{
								score += 5;
							}
							newenemy[t].NewEnemy_Hit = true;
							//이후 생성 안되는 버그 해결
							newenemy[t].init((float)(SCREEN_WIDTH + (rand() % 300)), rand() % SCREEN_HEIGHT - 50);
							newenemy[i].HP = 10;
						}
					}
				}
				//호밍미사일이 플레이어 미사일과 충돌시
				for (int k = 0; k < NewENEMY_NUM; k++)
				{
					if (bull3[i].check_collision(newenemybull[k].x_pos, newenemybull[k].y_pos) == true)
					{
						newenemybull[k].HP -= 1;
						if (newenemybull[k].HP <= 0)
						{
							newenemybull[k].hide();
						}
					}
				}
				if (bull3[i].check_collision(mushroom.x_pos, mushroom.y_pos + 45) == true)
				{
					bull3[i].hide();
				}

				if (bull3[i].check_collision(Boss.x_pos, Boss.y_pos + 45) == true)
				{
					Boss.HP -= 1;
					if (Boss.HP <= 0)
					{
						Boss.hide();
					}
				}
			}
		}

		/////////////////////
		//적들 충돌 처리  및 생성
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].show() == false && Boss.Boss_Exist == false)
			{
				enemy[i].active();
				enemy[i].init((float)(SCREEN_WIDTH + (rand() % 200)), rand() % SCREEN_HEIGHT - 50);

			}
			if (enemy[i].show() == true)
			{
				if (enemy[i].x_pos < -100 || enemy[i].y_pos >= SCREEN_HEIGHT || enemy[i].y_pos <= 0)
				{
					enemy[i].hide();
				}
				if (enemy[i].Enemy_Hit == true)
				{
					enemy[i].move();
					enemy[i].x_pos += 10; // 폭파시 전진이 아니라 정시상태에서 터지게 하기위해서
				}
				else
					enemy[i].move();
			}

			if (enemy[i].check_collision(hero.x_pos, hero.y_pos) == true)
			{
				hero.Hero_hit = true;
				score -= 1;
				enemy[i].hide();
			}

			if (hero.check_collision(enemy[i].x_pos, enemy[i].y_pos) == true)
			{
			}
		}

		//적 총알 처리
		for (int j = 0; j < ENEMY_NUM; j++)
		{
			if (enemy[j].x_pos < (SCREEN_WIDTH - 300) + rand() % 150 && Ebullet[j].show() == false)
			{
				Ebullet[j].active();
				Ebullet[j].init(enemy[j].x_pos, enemy[j].y_pos);
			}
		}
		//적 총알 처리
		for (int t = 0; t < ENEMY_NUM; t++)
		{
			if (Ebullet[t].show() == true)
			{
				if (Ebullet[t].x_pos < -100)
					Ebullet[t].hide();

				else
					Ebullet[t].move();
			}

			if (Ebullet[t].check_collision(hero.x_pos, hero.y_pos) == true)
			{
				score -= 3;
				hero.Hero_hit = true;
				Ebullet[t].hide();
			}
		}



		/////////////////////////////////////////////
		//특수 적
		for (int i = 0; i < NewENEMY_NUM; i++)
		{
			if (newenemy[i].show() == false && Boss.Boss_Exist == false)
			{
				newenemy[i].active();
				newenemy[i].init((float)(SCREEN_WIDTH + (rand() % 400)), rand() % SCREEN_HEIGHT);
			}


			if (newenemy[i].show() == true)
			{
				if (newenemy[i].x_pos < -100 || newenemy[i].y_pos >= SCREEN_HEIGHT - 100 || newenemy[i].y_pos <= 100)
				{
					newenemy[i].hide();
					newenemy[i].HP = 10;
				}
				//if(newenemy[i].x_pos > -100)
				else
				{
					newenemy[i].move();
				}

			}

			if (newenemy[i].check_collision(hero.x_pos, hero.y_pos) == true || newenemy[i].HP <= 0)
			{
				hero.Hero_hit = true;
				score -= 1;
				newenemy[i].hide();
			}

			//플레이어와의 충돌
			if (hero.check_collision(newenemy[i].x_pos, newenemy[i].y_pos) == true)
			{
			}

		}
		/////////////////////////////////////////////////////////////
		//특수적의 호밍미사일 발사
		for (int i = 0; i < NewENEMY_NUM; i++)
		{
			if (newenemy[i].x_pos < (SCREEN_WIDTH - 300) + rand() % 150 && newenemybull[i].show() == false)
			{
				newenemybull[i].init(newenemy[i].x_pos, newenemy[i].y_pos);
				newenemybull[i].active();

			}
		}

		for (int j = 0; j < NewENEMY_NUM; j++)
		{
			if (newenemybull[j].show() == true)
			{
				if (newenemybull[j].x_pos < -100)
					newenemybull[j].hide();
				else
				{
					newenemybull[j].HomingBullet(newenemybull[j].x_pos, newenemybull[j].y_pos, hero.x_pos, hero.y_pos, 5);
				}
			}

			if (newenemybull[j].check_collision(hero.x_pos, hero.y_pos) == true)
			{
				hero.Hero_hit = true;
				score -= 0.5f;
				newenemybull[j].hide();
			}

			//플레이어와의 충돌
			if (hero.check_collision(newenemybull[j].x_pos, newenemybull[j].y_pos) == true)
			{
			}
		}

		/////////////////////////////////////////////////////////////
		//총알 관통불가 오브젝트
		if (mushroom.show() == false && Boss.Boss_Exist == false)
		{
			mushroom.active();
			mushroom.init((float)(SCREEN_WIDTH + (rand() % 400)), rand() % SCREEN_HEIGHT - 100);
		}
		if (mushroom.show() == true)
		{
			if (mushroom.x_pos < -500 || mushroom.y_pos >= SCREEN_HEIGHT - 300 || mushroom.y_pos <= 300)
			{
				mushroom.hide();
			}
			else
			{
				mushroom.move();
			}

			if (mushroom.check_collision(hero.x_pos, hero.y_pos) == true)
			{
				hero.Hero_hit = true;
				score -= 5;
				mushroom.hide();
			}
		}
		/////////////////////////////////////////////
		//보스 등장
		if (score >= 300 && Boss.Boss_Exist == false)
		{
			Boss.Boss_Check = true;
			Boss.Boss_Exist = true;
		}

		if (Boss.Boss_Check)
		{
			Boss.init(hero.x_pos + 1000, 350);
			Boss.Boss_Check = false;
		}

		if (Boss.Boss_Exist)
		{
			Boss.move(Boss.x_pos, Boss.y_pos);
			if (Boss.x_pos < 1100)
			{
				//보스 첫번쨰 총알
				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Boss.x_pos < SCREEN_WIDTH - 50 && Bossbull1[i].show() == false)
					{
						Bossbull1[i].init(Boss.x_pos + 50, Boss.y_pos + 150);
						Bossbull1[i].active();
					}
				}

				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Bossbull1[i].show() == true)
					{
						if (Bossbull1[i].x_pos < -150)
						{
							Bossbull1[i].hide();
						}
						else
						{
							Bossbull1[i].move();
						}
					}

					if (Bossbull1[i].check_collision(hero.x_pos, hero.y_pos) == true)
					{
						hero.Hero_hit = true;
						score -= 0.5f;
						Bossbull1[i].hide();
					}

					if (hero.check_collision(Bossbull1[i].x_pos, Bossbull1[i].y_pos) == true)
					{

					}
				}
				//보스 두번째 총알
				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Boss.x_pos < SCREEN_WIDTH - 50 && Bossbull2[i].show() == false)
					{
						Bossbull2[i].InitAimingBullet(hero.x_pos, hero.y_pos, Boss.x_pos, Boss.y_pos, 15, Bossbull2[i].x_pos, Bossbull2[i].y_pos, Bossbull2[i].vx, Bossbull2[i].vy);
						Bossbull2[i].active();
					}
				}
				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Bossbull2[i].show() == true)
					{
						if (Bossbull2[i].x_pos < -20)
						{
							Bossbull2[i].hide();
						}
						else
						{

							Bossbull2[i].AimingBullet(Bossbull2[i].x_pos, Bossbull2[i].y_pos, Bossbull2[i].vx, Bossbull2[i].vy); // 대각선 직진탄
						}
					}

					if (Bossbull2[i].check_collision(hero.x_pos, hero.y_pos) == true)
					{
						score -= 1;
						hero.Hero_hit = true;
						Bossbull2[i].hide();
					}

					if (hero.check_collision(Bossbull2[i].x_pos, Bossbull2[i].y_pos) == true)
					{
			
					}
				}

				//보스 세번째 총알
				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Boss.x_pos < SCREEN_WIDTH - 50 && Bossbull2[i].show() == false)
					{
						Bossbull3[i].InitAimingBullet2(hero.x_pos, hero.y_pos, Boss.x_pos, Boss.y_pos, 20, Bossbull3[i].x_pos, Bossbull3[i].y_pos, Bossbull3[i].vx, Bossbull3[i].vy);
						Rand_DroppingBullet = (float)((float)((float)(rand() % 10) / 10) + 0.5); // 포물선 탄 변수
						Bossbull3[i].active();
					}
				}

				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Bossbull3[i].show() == true)
					{
						if (Bossbull3[i].x_pos < -20)
						{
							Bossbull3[i].hide();
						}
						else
						{
							Bossbull3[i].DroppingBullet_Up(Bossbull3[i].x_pos, Bossbull3[i].y_pos, Rand_DroppingBullet, Bossbull3[i].vx, Bossbull3[i].vy);
						}
					}

					if (Bossbull3[i].check_collision(hero.x_pos, hero.y_pos) == true)
					{
						hero.Hero_hit = true;
						Bossbull3[i].hide();
					}

					if (hero.check_collision(Bossbull3[i].x_pos, Bossbull3[i].y_pos) == true)
					{

					}
				}

				//보스 네번째 총알
				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Boss.x_pos < SCREEN_WIDTH - 50 && Bossbull1[i].show() == false)
					{
						Bossbull4[i].init(Boss.x_pos + 50, Boss.y_pos + 150);
						Bossbull4[i].active();
					}
				}

				for (int i = 0; i < BossBullLimit; i++)
				{
					if (Bossbull4[i].show() == true)
					{
						if (Bossbull4[i].x_pos < -150)
						{
							Bossbull4[i].hide();
						}
						else
						{
							Bossbull4[i].move();
						}
					}

					if (Bossbull4[i].check_collision(hero.x_pos, hero.y_pos) == true)
					{
						score -= 1;
						hero.Hero_hit = true;
						Bossbull4[i].hide();
					}

					if (hero.check_collision(Bossbull4[i].x_pos, Bossbull4[i].y_pos) == true)
					{

					}
				}
			}
		}
	}
}

// this is the function used to render a single frame
void render_frame(void)
{
	////////////////////////////////////////////////////////////
	//타이틀
	if (KEY_DOWN(VK_SPACE))
	{
		Title = false;
		InGame = true;
		Game_over = false;
	}

	if (Title == true)
	{
		//음악 재생
		mciSendCommand(2, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
		//mciSendCommand(2, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;


												 RECT part;
												 SetRect(&part, xpos, 0, xpos + 181, 128);
												 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
												 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
												 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
												 */


		RECT part8;
		SetRect(&part8, 0, 0, 1240, 800);
		D3DXVECTOR3 center8(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position8(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_Title, &part8, &center8, &position8, D3DCOLOR_ARGB(255, 255, 255, 255));

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		
		//폰트

		return;
	}
	////////////////////////////////////////////////////////////////////
	//인게임

	if (InGame == true)
	{
		if (score < 0)
		{
			InGame = false;
			Game_over = true;
		}
		//음악닫고 재생
		mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;


												 RECT part;
												 SetRect(&part, xpos, 0, xpos + 181, 128);
												 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
												 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
												 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
												 */

		//배경화면
		RECT part6;
		SetRect(&part6, 0, 0, 1240, 800);
		D3DXVECTOR3 center6(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position6(back[0].x_pos, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_BackGround1, &part6, &center6, &position6, D3DCOLOR_ARGB(255, 255, 255, 255));

		//배경화면2
		RECT part7;
		SetRect(&part7, 0, 0, 1240, 800);
		D3DXVECTOR3 center7(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position7(back[1].x_pos, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_BackGround2, &part7, &center7, &position7, D3DCOLOR_ARGB(255, 255, 255, 255));


		//주인공 애니메이션
		if (hero.Hero_hit == false)
		{
			RECT part_1;
			SetRect(&part_1, 0, 0, 60, 60);
			D3DXVECTOR3 center_1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position_1(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
			Hero_anicounter++;
			if (Hero_anicounter >= 12)
			{
				Hero_anicounter = 0;
			}
			switch (Hero_anicounter / 3)
			{
			case 0:
				d3dspt->Draw(sprite_hero_1, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 1:
				d3dspt->Draw(sprite_hero_2, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 2:
				d3dspt->Draw(sprite_hero_3, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 3:
				d3dspt->Draw(sprite_hero_4, &part_1, &center_1, &position_1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			}
		}
		//주인공에게 물체가 히트시
		if (hero.Hero_hit == true)
		{
			RECT partHit_1;
			SetRect(&partHit_1, 0, 0, 60, 60);
			D3DXVECTOR3 centerHit_1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 positionHit_1(hero.x_pos, hero.y_pos, 0.0f);    // position at 50, 50 with no depth
			Hero_Hit_anicounter++;
			if (Hero_Hit_anicounter >= 10)
			{
				Hero_Hit_anicounter = 0;
			}
			switch (Hero_Hit_anicounter / 5)
			{
			case 0:
				d3dspt->Draw(sprite_Hit_hero_1, &partHit_1, &centerHit_1, &positionHit_1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;
			case 1:
				d3dspt->Draw(sprite_Hit_hero_2, &partHit_1, &centerHit_1, &positionHit_1, D3DCOLOR_ARGB(255, 255, 255, 255));
				break;

			}
		}

		
		
		if (hero.Hero_hit == true)
		{
			Hero_Hit_counter++;
		}

		if (Hero_Hit_counter % 20 == 0)
		{
			Hero_Hit_counter = 0;
			hero.Hero_hit = false;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//첫번째 총알
		CoinBullet_anicounter_1++;
		if (CoinBullet_anicounter_1 >= 30)
		{
			CoinBullet_anicounter_1 = 0;
		}

		////첫번째총알
		for (int i = 0; i < BullLimit; i++)
		{
			if (bull[i].bShow == true)
			{
				RECT part1_1;
				SetRect(&part1_1, 0, 0, 40, 40);
				D3DXVECTOR3 center1_1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1_1(bull[i].x_pos, bull[i].y_pos + 5.0f, 0.0f);    // position at 50, 50 with no depth

				switch (CoinBullet_anicounter_1 / 3)
				{
				case 0:
					d3dspt->Draw(sprite_bullet_1, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 1:
					d3dspt->Draw(sprite_bullet_2, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 2:
					d3dspt->Draw(sprite_bullet_3, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 3:
					d3dspt->Draw(sprite_bullet_4, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 4:
					d3dspt->Draw(sprite_bullet_5, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 5:
					d3dspt->Draw(sprite_bullet_6, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 6:
					d3dspt->Draw(sprite_bullet_7, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 7:
					d3dspt->Draw(sprite_bullet_8, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 8:
					d3dspt->Draw(sprite_bullet_9, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 9:
					d3dspt->Draw(sprite_bullet_10, &part1_1, &center1_1, &position1_1, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
			}
		}


		//두번째 총알
		CoinBullet_anicounter_2++;
		if (CoinBullet_anicounter_2 >= 30)
		{
			CoinBullet_anicounter_2 = 0;
		}
		for (int i = 0; i < BullLimit; i++)
		{
			if (bull2[i].bShow == true)
			{
				RECT part1_2;
				SetRect(&part1_2, 0, 0, 40, 40);
				D3DXVECTOR3 center1_2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1_2(bull2[i].x_pos, bull2[i].y_pos + 5.0f, 0.0f);    // position at 50, 50 with no depth

				switch (CoinBullet_anicounter_2 / 3)
				{
				case 0:
					d3dspt->Draw(sprite_bullet_1, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 1:
					d3dspt->Draw(sprite_bullet_2, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 2:
					d3dspt->Draw(sprite_bullet_3, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 3:
					d3dspt->Draw(sprite_bullet_4, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 4:
					d3dspt->Draw(sprite_bullet_5, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 5:
					d3dspt->Draw(sprite_bullet_6, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 6:
					d3dspt->Draw(sprite_bullet_7, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 7:
					d3dspt->Draw(sprite_bullet_8, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 8:
					d3dspt->Draw(sprite_bullet_9, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 9:
					d3dspt->Draw(sprite_bullet_10, &part1_2, &center1_2, &position1_2, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
			}
		}


		//세번째 총알
		CoinBullet_anicounter_3++;
		if (CoinBullet_anicounter_3 >= 30)
		{
			CoinBullet_anicounter_3 = 0;
		}
		for (int i = 0; i < BullLimit; i++)
		{
			if (bull3[i].bShow == true)
			{
				RECT part1_3;
				SetRect(&part1_3, 0, 0, 40, 40);
				D3DXVECTOR3 center1_3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
				D3DXVECTOR3 position1_3(bull3[i].x_pos, bull3[i].y_pos + 5.0f, 0.0f);    // position at 50, 50 with no depth
		
				switch (CoinBullet_anicounter_3 / 3)
				{
				case 0:
					d3dspt->Draw(sprite_bullet_1, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 1:
					d3dspt->Draw(sprite_bullet_2, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 2:
					d3dspt->Draw(sprite_bullet_3, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 3:
					d3dspt->Draw(sprite_bullet_4, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 4:
					d3dspt->Draw(sprite_bullet_5, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 5:
					d3dspt->Draw(sprite_bullet_6, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 6:
					d3dspt->Draw(sprite_bullet_7, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 7:
					d3dspt->Draw(sprite_bullet_8, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 8:
					d3dspt->Draw(sprite_bullet_9, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 9:
					d3dspt->Draw(sprite_bullet_10, &part1_3, &center1_3, &position1_3, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}
			}
		}

		/*

		////슈퍼총알
		if (Superbullet.bShow == true)
		{
			RECT part3;
			SetRect(&part3, 0, 0, 100, 100);
			D3DXVECTOR3 center3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position3(Superbullet.x_pos, Superbullet.y_pos, 0.0f);    // position at 50, 50 with no depth
			d3dspt->Draw(sprite_superbullet, &part3, &center3, &position3, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		*/

		EnemyGundam_anicounter++;
		if (EnemyGundam_anicounter >= 6)
		{
			EnemyGundam_anicounter = 0;
		}
		if (Boss.Boss_Exist == false)
		{
			////에네미 
			RECT part2;
			SetRect(&part2, 0, 0, 60, 90);
			D3DXVECTOR3 center2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				D3DXVECTOR3 position2(enemy[i].x_pos, enemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth
				if (enemy[i].show() == true && enemy[i].Enemy_Hit == false)
				{
					switch (EnemyGundam_anicounter / 3)
					{
					case 0:
						d3dspt->Draw(sprite_enemy_1, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 1:
						d3dspt->Draw(sprite_enemy_2, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					}
				}
				if (enemy[i].Enemy_Hit == true)
				{
					EnemyGundam_Hit_anicounter++;
					if (EnemyGundam_Hit_anicounter >= 39)
					{
						enemy[i].Enemy_Hit = false;
						EnemyGundam_Hit_anicounter = 0;
					}
					switch (EnemyGundam_Hit_anicounter / 3)
					{
					case 0:
						d3dspt->Draw(sprite_enemy_Hit_1, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 1:
						d3dspt->Draw(sprite_enemy_Hit_2, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 2:
						d3dspt->Draw(sprite_enemy_Hit_3, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 3:
						d3dspt->Draw(sprite_enemy_Hit_4, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 4:
						d3dspt->Draw(sprite_enemy_Hit_5, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 5:
						d3dspt->Draw(sprite_enemy_Hit_6, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 6:
						d3dspt->Draw(sprite_enemy_Hit_7, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 7:
						d3dspt->Draw(sprite_enemy_Hit_8, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 8:
						d3dspt->Draw(sprite_enemy_Hit_9, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 9:
						d3dspt->Draw(sprite_enemy_Hit_10, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 10:
						d3dspt->Draw(sprite_enemy_Hit_11, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 11:
						d3dspt->Draw(sprite_enemy_Hit_12, &part2, &center2, &position2, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 12 :
						enemy[i].hide();
						break;
					}
				}
			}


			//적총알
			RECT part4;
			SetRect(&part4, 0, 0, 30, 30);
			D3DXVECTOR3 center4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner	


			for (int i = 0; i < ENEMY_NUM; i++)
			{
				D3DXVECTOR3 position4(Ebullet[i].x_pos, Ebullet[i].y_pos, 0.0f);    // position at 50, 50 with no depth		
				d3dspt->Draw(sprite_enemybullet, &part4, &center4, &position4, D3DCOLOR_ARGB(255, 255, 255, 255));
			}




			NewEnemyGundam_anicounter++;
			if (NewEnemyGundam_anicounter >= 12)
			{
				NewEnemyGundam_anicounter = 0;
			}
			//새로운 적
			RECT part5;
			SetRect(&part5, 0, 0, 100, 95);
			D3DXVECTOR3 center5(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			for (int i = 0; i < NewENEMY_NUM; i++)
			{
				D3DXVECTOR3 position5(newenemy[i].x_pos, newenemy[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
				switch (NewEnemyGundam_anicounter / 3)
				{
				case 0:
					d3dspt->Draw(sprite_Newenemy_1, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 1:
					d3dspt->Draw(sprite_Newenemy_2, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 2:
					d3dspt->Draw(sprite_Newenemy_3, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				case 3:
					d3dspt->Draw(sprite_Newenemy_4, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
					break;
				}

				if (newenemy[i].NewEnemy_Hit == true)
				{
					NewEnemyGundam_Hit_anicounter++;
					if (EnemyGundam_Hit_anicounter >= 39)
					{
						newenemy[i].NewEnemy_Hit = false;
						NewEnemyGundam_Hit_anicounter = 0;
					}
					switch (NewEnemyGundam_Hit_anicounter / 3)
					{
					case 0:
						d3dspt->Draw(sprite_enemy_Hit_1, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 1:
						d3dspt->Draw(sprite_enemy_Hit_2, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 2:
						d3dspt->Draw(sprite_enemy_Hit_3, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 3:
						d3dspt->Draw(sprite_enemy_Hit_4, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 4:
						d3dspt->Draw(sprite_enemy_Hit_5, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 5:
						d3dspt->Draw(sprite_enemy_Hit_6, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 6:
						d3dspt->Draw(sprite_enemy_Hit_7, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 7:
						d3dspt->Draw(sprite_enemy_Hit_8, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 8:
						d3dspt->Draw(sprite_enemy_Hit_9, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 9:
						d3dspt->Draw(sprite_enemy_Hit_10, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 10:
						d3dspt->Draw(sprite_enemy_Hit_11, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 11:
						d3dspt->Draw(sprite_enemy_Hit_12, &part5, &center5, &position5, D3DCOLOR_ARGB(255, 255, 255, 255));
						break;
					case 12:
						newenemy[i].hide();
						break;
					}
				}
			}
			///////////////////////////////
			//특수적 호밍미사일
				RECT part11;
				SetRect(&part11, 0, 0, 60, 60);
				D3DXVECTOR3 center11(0.0f, 0.0f, 0.0f);    // center at the upper-left corner	
				for (int i = 0; i < NewENEMY_NUM; i++)
				{
					D3DXVECTOR3 position11(newenemybull[i].x_pos, newenemybull[i].y_pos, 0.0f);    // position at 50, 50 with no depth		
					d3dspt->Draw(sprite_Newenemymissile, &part11, &center11, &position11, D3DCOLOR_ARGB(255, 255, 255, 255));
				} 


			//총알 통과불가 오브젝트
			RECT part10;
			SetRect(&part10, 0, 0, 300, 300);
			D3DXVECTOR3 center10(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
			D3DXVECTOR3 position10(mushroom.x_pos, mushroom.y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_MushroomEnemy, &part10, &center10, &position10, D3DCOLOR_ARGB(255, 255, 255, 255));
		}


		if (hero.Hero_hit == true)
		{
			Hero_Hit_counter++;
		}

		if (Hero_Hit_counter % 20 == 0)
		{
			Hero_Hit_counter = 0;
			hero.Hero_hit = false;
		}


		RECT part12;
		SetRect(&part12, 0, 0, 400, 300);
		D3DXVECTOR3 center12(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position12(Boss.x_pos, Boss.y_pos, 0.0f);    // position at 50, 50 with no depth	
		d3dspt->Draw(sprite_Boss, &part12, &center12, &position12, D3DCOLOR_ARGB(255, 255, 255, 255));

		//보스 총알
		RECT part13_1;
		SetRect(&part13_1, 0, 0, 40, 40);
		D3DXVECTOR3 center13_1(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		for (int i = 0; i < BossBullLimit; i++)
		{
			D3DXVECTOR3 position13_1(Bossbull1[i] .x_pos, Bossbull1[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_BossMissile, &part13_1, &center13_1, &position13_1, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		RECT part13_2;
		SetRect(&part13_2, 0, 0, 40, 40);
		D3DXVECTOR3 center13_2(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		for (int i = 0; i < BossBullLimit; i++)
		{
			D3DXVECTOR3 position13_2(Bossbull2[i].x_pos, Bossbull2[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_BossMissile, &part13_2, &center13_2, &position13_2, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		RECT part13_3;
		SetRect(&part13_3, 0, 0, 40, 40);
		D3DXVECTOR3 center13_3(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		for (int i = 0; i < BossBullLimit; i++)
		{
			D3DXVECTOR3 position13_3(Bossbull3[i].x_pos, Bossbull3[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_BossMissile, &part13_3, &center13_3, &position13_3, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		RECT part13_4;
		SetRect(&part13_4, 0, 0, 40, 40);
		D3DXVECTOR3 center13_4(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		for (int i = 0; i < BossBullLimit; i++)
		{
			D3DXVECTOR3 position13_4(Bossbull4[i].x_pos, Bossbull4[i].y_pos, 0.0f);    // position at 50, 50 with no depth	
			d3dspt->Draw(sprite_BossMissile, &part13_4, &center13_4, &position13_4, D3DCOLOR_ARGB(255, 255, 255, 255));
		}


		/*
		if (font)
		{
			font->DrawTextA(NULL, message.c_str(), -1, &fRectangle, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		*/

		RECT part25;
		SetRect(&part25, 0, 0, 128, 64);
		D3DXVECTOR3 center25(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position25(SCREEN_WIDTH - (32 * 4), 0.0f, 0.0f);    // position at 50, 50 with no depth	
		d3dspt->Draw(sprite_ScoreBox, &part25, &center25, &position25, D3DCOLOR_ARGB(255, 255, 255, 255));
		Score_Manager();
		
		//
		//sprite_ScoreBox

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		//폰트

		return;
	}

	///////////////////////////////////////////////////////////
	//게임오버

	if (Game_over == true)
	{
		if (KEY_DOWN(VK_RETURN))
		{
			Title = true;
			Game_over = false;
		}

		mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		mciSendCommand(2, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		// clear the window to a deep blue
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		d3ddev->BeginScene();    // begins the 3D scene

		d3dspt->Begin(D3DXSPRITE_ALPHABLEND);    // // begin sprite drawing with transparency

												 //UI 창 렌더링 


												 /*
												 static int frame = 21;    // start the program on the final frame
												 if(KEY_DOWN(VK_SPACE)) frame=0;     // when the space key is pressed, start at frame 0
												 if(frame < 21) frame++;     // if we aren't on the last frame, go to the next frame

												 // calculate the x-position
												 int xpos = frame * 182 + 1;


												 RECT part;
												 SetRect(&part, xpos, 0, xpos + 181, 128);
												 D3DXVECTOR3 center(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
												 D3DXVECTOR3 position(150.0f, 50.0f, 0.0f);    // position at 50, 50 with no depth
												 d3dspt->Draw(sprite, &part, &center, &position, D3DCOLOR_ARGB(127, 255, 255, 255));
												 */

												 //배경화면

		RECT part9;
		SetRect(&part9, 0, 0, 1240, 800);
		D3DXVECTOR3 center9(0.0f, 0.0f, 0.0f);    // center at the upper-left corner
		D3DXVECTOR3 position9(0.0f, 0.0f, 0.0f);    // position at 50, 50 with no depth
		d3dspt->Draw(sprite_over, &part9, &center9, &position9, D3DCOLOR_ARGB(255, 255, 255, 255));

		d3dspt->End();    // end sprite drawing

		d3ddev->EndScene();    // ends the 3D scene

		d3ddev->Present(NULL, NULL, NULL, NULL);
		//폰트

		return;
	}
}


//스코어
void Score_Manager(void)
{
	RECT part20;
	D3DXVECTOR3 center20(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 position20(SCREEN_WIDTH-(32*4), 0, 0.0f);
	SetRect(&part20, 0, 0, 32, 64);
	int score_temp = score;
	int temp;
	temp = score_temp / 1000;
	switch (temp)
	{
	case 0:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number0.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;

	case 1:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number1.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 2:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number2.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 3:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number3.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 4:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number4.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 5:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number5.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 6:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number6.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 7:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number7.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 8:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number8.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	case 9:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number9.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SThou);    // load to sprite
		break;
	}

	d3dspt->Draw(sprite_SThou, &part20, &center20, &position20, D3DCOLOR_ARGB(255, 255, 255, 255));
	D3DXVECTOR3 position21(SCREEN_WIDTH - (32 * 3), 0, 0.0f);
	score_temp = score_temp % 1000;
	temp = score_temp / 100;

	switch (temp)
	{
	case 0:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number0.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;

	case 1:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number1.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 2:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number2.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 3:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number3.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 4:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number4.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 5:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number5.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 6:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number6.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 7:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number7.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 8:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number8.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	case 9:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number9.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SHund);    // load to sprite
		break;
	}
	d3dspt->Draw(sprite_SHund, &part20, &center20, &position21, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXVECTOR3 position22(SCREEN_WIDTH - (32 * 2), 0, 0.0f);

	score_temp = score_temp % 100;
	temp = score_temp / 10;
	switch (temp)
	{
	case 0:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number0.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;

	case 1:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number1.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 2:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number2.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 3:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number3.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 4:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number4.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 5:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number5.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 6:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number6.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 7:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number7.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 8:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number8.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	case 9:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number9.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_STen);    // load to sprite
		break;
	}

	d3dspt->Draw(sprite_STen, &part20, &center20, &position22, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXVECTOR3 position23(SCREEN_WIDTH - (32*1) , 0, 0.0f);

	score_temp = score_temp % 10;
	switch (score_temp)
	{
	case 0:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number0.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;

	case 1:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number1.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 2:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number2.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 3:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number3.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 4:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number4.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 5:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number5.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 6:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number6.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 7:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number7.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 8:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number8.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	case 9:
		D3DXCreateTextureFromFileEx(d3ddev,    // the device pointer
			L"Score/Number9.png",    // the file name
			D3DX_DEFAULT,    // default width
			D3DX_DEFAULT,    // default height
			D3DX_DEFAULT,    // no mip mapping
			NULL,    // regular usage
			D3DFMT_A8R8G8B8,    // 32-bit pixels with alpha
			D3DPOOL_MANAGED,    // typical memory handling
			D3DX_DEFAULT,    // no filtering
			D3DX_DEFAULT,    // no mip filtering
			D3DCOLOR_XRGB(255, 0, 255),    // the hot-pink color key
			NULL,    // no image info struct
			NULL,    // not using 256 colors
			&sprite_SOne);    // load to sprite
		break;
	}
	d3dspt->Draw(sprite_SOne, &part20, &center20, &position23, D3DCOLOR_ARGB(255, 255, 255, 255));
}

// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
	d3ddev->Release();
	d3d->Release();
	font->Release();
	//배경화면 해제 
	sprite_BackGround1->Release();
	sprite_BackGround2->Release();

	//플레이어 해제
	sprite_hero_1->Release();
	sprite_hero_2->Release();
	sprite_hero_3->Release();
	sprite_hero_4->Release();

	//히트 애니메이션
	sprite_Hit_hero_1->Release();
	sprite_Hit_hero_2->Release();

	//총알
	sprite_bullet_1->Release();
	sprite_bullet_2->Release();
	sprite_bullet_3->Release();
	sprite_bullet_4->Release();
	sprite_bullet_5->Release();
	sprite_bullet_6->Release();
	sprite_bullet_7->Release();
	sprite_bullet_8->Release();
	sprite_bullet_9->Release();
	sprite_bullet_10->Release();

	sprite_superbullet->Release();

	//적 해제
	sprite_enemy_1->Release();
	sprite_enemy_2->Release();

	sprite_MushroomEnemy->Release(); // 버섯

	//특수 적
	sprite_Newenemy_1->Release();
	sprite_Newenemy_2->Release();
	sprite_Newenemy_3->Release();
	sprite_Newenemy_4->Release();

	sprite_enemybullet->Release();
	sprite_Newenemymissile->Release();

	//보스
	sprite_Boss->Release();
	sprite_BossMissile->Release();

	//적들 피격시 애니메이션 해제 
	sprite_enemy_Hit_1->Release();
	sprite_enemy_Hit_2->Release();
	sprite_enemy_Hit_3->Release();
	sprite_enemy_Hit_4->Release();
	sprite_enemy_Hit_5->Release();
	sprite_enemy_Hit_6->Release();
	sprite_enemy_Hit_7->Release();
	sprite_enemy_Hit_8->Release();
	sprite_enemy_Hit_9->Release();
	sprite_enemy_Hit_10->Release();
	sprite_enemy_Hit_11->Release();
	sprite_enemy_Hit_12->Release();

	//타이틀 / 게임오버 해제
	sprite_Title->Release();
	sprite_over->Release();

	//스코어
	sprite_SThou->Release();
	sprite_SOne->Release();
	sprite_SHund->Release();
	sprite_STen->Release();
	sprite_ScoreBox->Release();




	//음악 닫기
	mciSendCommand(1, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	mciSendCommand(2, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	mciSendCommand(3, MCI_CLOSE, 0, (DWORD)(LPVOID)NULL);
	return;
}