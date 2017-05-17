#pragma once

#include "Scene.h"

template<typename Enum>				// Enum class�� �������� �˷��־� ���ڿ� �����ϴ� ���� ��ȯ�ϴ� �Լ��Դϴ�.
inline constexpr auto GetEnumValueByType(Enum enumerator) noexcept	// enum class E : int { a,b,c }; �� ��,
{																	// auto data = GetEnumValueByType(E::a);
	return static_cast<std::underlying_type_t<Enum>>(enumerator);	// data�� ������ int �̰�, ���� 0 �Դϴ�.
}

#define GetSceneEnumInt(Enum) GetEnumValueByType(CScene::CurrentScene::Enum)

class CFramework
{
private:
	HWND			m_hWnd{ NULL };
	HGLRC			m_hglRC{ NULL };
	RECTf			m_rcClient{ 0,0,0,0 };

	HDC				m_hDC = NULL;

	myCOLORREFf		m_clrBackBuffer{ 0.5f, 0.5f, 0.9f, 0.1f };

	CSoundManager	*m_SoundManager;

	CScene			*m_pCurrentScene;
	CScene			*m_arrScene[GetEnumValueByType(CScene::CurrentScene::count)];

	CCamera_OpenGL	*m_Camera;
	CCamera_OpenGL	*m_MiniMapCamera;
	CLight			*m_Light;
	CTextureLibraray*m_TextureLib;

	std::chrono::system_clock::time_point m_current_time;
	std::chrono::duration<double> m_timeElapsed; // �ð��� �󸶳� ������
	double m_fps;

	TCHAR m_CaptionTitle[TITLE_MX_LENGTH];
	int m_TitleLength;
	std::chrono::system_clock::time_point m_LastUpdate_time;
	std::chrono::duration<double> m_UpdateElapsed; // �ð��� �󸶳� ������

public:
	CFramework();
	~CFramework();

	bool OnCreate(HWND hWnd, const RECT& rc);
	bool OpenGLInit();
	void TextureLoad();
	void BuildScene();

	bool OnDestroy();
	
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	HRESULT OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void Update(float fTimeElapsed);
	
	void ClearBackgroundColor();
	void PreproccessingForRendering();
	void Rendering();
	void ReShape(int width, int height);

	void ChangeScene(CScene::CurrentScene tag, bool bDestroy = false);

	CSoundManager*		GetSoundManager() { return m_SoundManager; }
	CCamera_OpenGL*		GetMiniMapCamera() { return m_MiniMapCamera; }
	CCamera_OpenGL*		GetCamera() { return m_Camera; }
	CLight*				GetLight() { return m_Light; }
	CTextureLibraray*	GetTextureLib() { return m_TextureLib; }

	void FrameAdvance();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

