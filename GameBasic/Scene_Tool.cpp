#include "pch.h"
#include "Scene_Tool.h"

#include "KeyManager.h"
#include "ResManager.h"
#include "SceneManager.h"

#include "Tile.h"
#include "Core.h"

#include "resource.h"

Scene_Tool::Scene_Tool()
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::update()
{
	Scene::update();

	/*if (KEY_TAP(KEY::ENTER)) {
		ChangeSceneEvent(SCENE_TYPE::START);
	}*/

	SetTileIdx();
}

void Scene_Tool::Enter()
{
	Texture* tlieTexure = ResManager::Instance()->LoadTexture(L"Tile", L"Texture\\Tile.bmp");

	// Ÿ�� ����
	CreateTile(5, 5);

	Vec2 resolution = Core::Instance()->GetResolution();
	Camera::Instance()->SetLookAt(resolution / 2.f);
}

void Scene_Tool::Exit()
{
	DeleteAll();
}

void Scene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN)) {
		Vec2 mousePos = MOUSE_POS;

		// ���콺 ��ǥ�� ���� ��ǥ�� �˾ƾ� ��
		mousePos = Camera::Instance()->GetRenderPos(mousePos);

		UINT tileX = GetTileX();
		UINT tileY = GetTileY();

		UINT col = (UINT)mousePos.x / TILE_SIZE;
		UINT row = (UINT)mousePos.y / TILE_SIZE;

		UINT idx = row * tileX + col;

		const vector<Object*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((Tile*)vecTile[idx])->AddImgIdx();
	}
}


// ======================
// Tile Count Window Proc
// ======================
// ��� �Լ� �ƴϴ�.

INT_PTR _stdcall TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK){
			// GetDlgItemInt - ���ڿ��� �ϳ��� ���ڷ� �ٲ��ִ� �Լ�
			UINT xCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT yCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			Scene* curScene = SceneManager::Instance()->GetCurScene();
			
			// tool ������ Ȯ��
			// �ٿ� ĳ�����ؼ� ������� �´��� Ȯ���ϵ��� �Ѵ�.
			Scene_Tool* scene = dynamic_cast<Scene_Tool*>(curScene);
			assert(scene);

			scene->DeleteGroup(GROUP_TYPE::TILE);
			scene->CreateTile(xCount, yCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
			
		else if(LOWORD(wParam) == IDCANCEL)	{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}