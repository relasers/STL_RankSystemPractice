#include "TextureLib.h"

GLuint CTextureLibraray::g_nStartTexture = 0;

CTextureLibraray::CTextureLibraray()
{
}
CTextureLibraray::~CTextureLibraray()
{
}

void CTextureLibraray::SetTexture(LPCTSTR str)
{
	CImage img;
	img.Load(str);

	glBindTexture(GL_TEXTURE_2D, g_nStartTexture);
	
	int iColorTable = img.GetBPP() / 8;

	GLTextureData data
	{
		  g_nStartTexture
		, (iColorTable == 4)
		, GetCImageBits(img)
	};
	

	glTexImage2D(	  GL_TEXTURE_2D
					, 0
					, iColorTable
					, img.GetWidth(), img.GetHeight(), 0
					, (iColorTable == 3) ? GL_BGR_EXT : GL_BGRA_EXT
					, GL_UNSIGNED_BYTE 
					, data.GetData()
		);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	m_vTexData.push_back(data);
	g_nStartTexture++;
}

void CTextureLibraray::LoadTexture(size_t idx)
{
	glBindTexture(GL_TEXTURE_2D, m_vTexData[idx].textureIndex);
}

std::vector<GLubyte> GetCImageBits(const CImage & Cimg)
{
	// ���ϰ�
	std::vector<GLubyte> retval;

	// ��Ʈ��(DDB) ���� ���
	BITMAP bmp;
	GetObject(Cimg, sizeof(BITMAP), &bmp);

	// ��Ʈ��(DIB) ���� ����
	BITMAPINFOHEADER bmih{ 0 };

	// bitmap header�� ���� ����
	bmih.biSize = sizeof(BITMAPINFOHEADER);

	bmih.biWidth = bmp.bmWidth;    // ����
	bmih.biHeight = bmp.bmHeight;  // ����

	// ��� ��ġ�� ���� ���� ��. ������ 1�� ����.
	bmih.biPlanes = 1;
	// �ȼ� �� ��Ʈ ��(Bit per Pixel).
	// R8G8B8 = 24�� �⺻������ �������� A8�� �پ 32�� ����Ѵ�.
	bmih.biBitCount = Cimg.GetBPP();
	// RGB ����. 32 BPP�� ��� BI_BITFIELDS�� ��ȿ
	bmih.biCompression = (BI_RGB);

	// ��Ʈ��(DIB) ������ ����
	// �������� ũ�⸦ �˾Ƴ���.
	HDC hDC = ::GetDC(NULL);
	{
		// �̹����� ũ�⸦ Ȯ���ϱ� ���� lpvBits�� NULL�� �ְ�
		// bitmap header�� biSizeImage�� ���� �Է¹޴´�.
		::GetDIBits(hDC, Cimg, 0, bmp.bmHeight, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		// ȹ���� ��Ʈ�� ����� �ް�
		// ������ ���� ������ Ȯ���Ѵ�.
		retval.resize(bmih.biSizeImage);
		// �迭�� �ȼ� ������ ����ȴ�.
		::GetDIBits(hDC, Cimg, 0, bmp.bmHeight, &(retval[0]), (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	}
	::ReleaseDC(NULL, hDC);

	return retval;
}
