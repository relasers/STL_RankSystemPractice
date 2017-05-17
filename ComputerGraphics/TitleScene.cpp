#include "stdafx.h"
#include "TitleScene.h"

#include "Framework.h"

CTitleScene::CTitleScene()
{
}
CTitleScene::~CTitleScene()
{
	m_timer = 0.0f;
}

void CTitleScene::Update(float fTimeElapsed)
{
	m_SoundManager->Update(fTimeElapsed);
	m_timer += fTimeElapsed;
	if(m_timer > 3.0f)m_Input = true;
}

void CTitleScene::Rendering()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, CLIENT_WIDTH, CLIENT_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	CTextureLibraray::UsingTexture2D();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
		m_TextureLib->LoadTexture(CTextureLibraray::TextureIndex::TITLE);
		glColor4f(1, 1, 1, 1);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex2f(0, CLIENT_HEIGHT);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(CLIENT_WIDTH, CLIENT_HEIGHT);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(CLIENT_WIDTH, 0);
		}
		glEnd();
	}
	CTextureLibraray::StopUsingTexture2D();
}

void CTitleScene::RendMiniMap()
{
	
}

bool CTitleScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		if (m_Input)
		{
			m_pCamera->SetProjection(CCamera_OpenGL::ProjectionType::Perspective);
			m_SoundManager->PlaySnd_BGM(CSoundManager::BGM_SOUND::Stop_BGM);
			m_SoundManager->PlaySnd_BGM(CSoundManager::BGM_SOUND::Stage_BGM);
			m_pFramework->ChangeScene(CScene::CurrentScene::Main, true);
			m_timer = 0.0f;
			m_Input = false;
		}
		break;
	}
	return false;
}

bool CTitleScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	}
	return false;
}

bool CTitleScene::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_SIZE:
		break;
	case WM_DESTROY:
		break;
	}
	return false;
}

void CTitleScene::BuildObjects(CFramework * myFramework, HWND hWnd, CurrentScene tag)
{
	CScene::BuildObjects(myFramework, hWnd, tag);
	m_SoundManager = m_pFramework->GetSoundManager();
	m_pCamera = m_pFramework->GetCamera();
	m_pLight = m_pFramework->GetLight();
	m_TextureLib = m_pFramework->GetTextureLib();
	
}

void CTitleScene::ReleaseObjects()
{
}