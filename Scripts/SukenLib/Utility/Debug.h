#pragma once
#include"../Manager.h"
#include "DxLib.h"
#include "Utility.h"
#include<vector>
#include<windows.h>

#define DEBUG_PRINT_VALUE(value) debug.PrintValue( #value ,value)

namespace suken{

/**
*	@brief �������C�u�����Ǝ��f�o�b�O�p�֐�
*	exe�̓�����ꎞ�I�Ɏ~�߁A�G���[���b�Z�[�W��\������B
*	��������̑�������邱�Ƃŕ����\�B
*	@param format �o�͂���x�����̏����t��������̃A�h���X
*/
inline void WarningSK(const char* format, ...)
{
#ifdef DEBUG
	 char tmpchar[256];
    sprintf_s(tmpchar, "�x�� : \n\n%s\n\n", format);
	printfDx(tmpchar);
	printfDx("PRESS ANY KEY TO CONTINUE...");
    ScreenFlip();
    WaitKey();
    clsDx();
    ClearDrawScreen();
#endif
}

///�G���[&�f�o�b�O�o�͗p�֐�///////////////////////////////////////////////////////
/**
*	@brief ����
*/
#define ERRORDX(...)     ErrorDx(__LINE__, __FUNCTION__, __FILE__,  __VA_ARGS__)
/**
*	@brief ����
*/
#define WARNINGDX(...) WarningDx(__LINE__, __FUNCTION__, __FILE__,  __VA_ARGS__)
/**
*	@brief ����
*/
#define DEBUGDX(...)     DebugDx(__LINE__, __FUNCTION__, __FILE__,  __VA_ARGS__)
 
/**
*	@brief ����
*/
inline void myprintLog(const char* filename, const char* format, va_list args)
{
    #ifndef MYLOG_DISABLE
        FILE *fp;
        errno_t error;
        char txtfilename[1024];
        sprintf_s(txtfilename, "%s.txt", filename);
        if(error = fopen_s(&fp, txtfilename, "a") != 0){
            return;
        }else{
            char tmpchar[1024];
            vsprintf_s(tmpchar, format, args);
            fprintf_s(fp, "[%s]:%s\n", GetNowSystemTimeString().c_str(), tmpchar);
            fclose(fp);
        }
    #endif
}

/**
*	@brief ����
*	@param value ����
*/
inline void myLog(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    myprintLog("MyLog", format, args);
    va_end(args);
}

/**
*	@brief ����
*	@param value ����
*/
inline void myLogf(const char* filename, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    myprintLog(filename, format, args);
    va_end(args);
}

/**
*	@brief ����
*	@param value ����
*/
inline void myprintfDx(const char*format, va_list args, const char* filename=nullptr, int line=0)
{
    char string[1024];
    vsprintf_s(string, format, args);   //va_start��va_end�͌Ăяo�����ł���
    if (filename!=nullptr) sprintf_s(string, "%s\n->%s(%d)\n", string, filename, line);
 
    myLogf("MyLog_Printed", "PRINT: %s", string);
    printfDx(string);
    ScreenFlip();
    WaitKey();
    clsDx();
    ClearDrawScreen();
}

/**
*	@brief ����
*	@param value ����
*/
inline void ErrorDx(int line, const char* func, const char* filename, const char* format, ...)
{
    char tmpchar[256];
    va_list args;   va_start(args, format);
    sprintf_s(tmpchar, "Error->%s\n->%s", format, func);
    myprintfDx(tmpchar, args, filename, line);
    va_end(args);
}

/**
*	@brief ����
*	@param value ����
*/
inline void ErrorDx(const char* format, char* filename, int line, ...)
{
    va_list args;
    va_start(args, line);
    myprintfDx(format, args, filename, line);
    va_end(args);
}

/**
*	@brief ����
*	@param value ����
*/
inline void ErrorDx(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    myprintfDx(format, args);
    va_end(args);
}

/**
*	@brief ����
*	@param value ����
*/
inline void WarningDx(int line, const char* func, const char* filename, const std::string format, ...)
{
    #ifndef WARNINGDX_DISABLE 
        char tmpchar[256];
        va_list args;   va_start(args, format);
        sprintf_s(tmpchar, "Warning->%s\n->%s", format, func);
        myprintfDx(tmpchar, args, filename, line);
        va_end(args);
    #endif
}

/**
*	@brief ����
*	@param value ����
*/
inline void WarningDx(const char* format, char* filename, int line, ...)
{
    #ifndef WARNINGDX_DISABLE 
        va_list args;
        va_start(args, line);
        myprintfDx(format, args, filename, line);
        va_end(args);
    #endif
}

/**
*	@brief ����
*	@param value ����
*/
inline void WarningDx(const char* format, ...)
{
    #ifndef WARNINGDX_DISABLE 
        va_list args;
        va_start(args, format);
        myprintfDx(format, args);
        va_end(args);
    #endif
}

/**
*	@brief ����
*	@param value ����
*/
inline void DebugDx(int line, const char* func, const char* filename, const char* format, ...)
{
    #ifndef DEBUGDX_DISABLE 
        char tmpchar[256];
        va_list args;   va_start(args, format);
        sprintf_s(tmpchar, "Debug->%s\n->%s", format, func);
        myprintfDx(tmpchar, args, filename, line);
        va_end(args);
    #endif
}

/**
*	@brief ����
*	@param value ����
*/
inline void DebugDx(const char* format, const char* filename, int line, ...)
{
    #ifndef DEBUGDX_DISABLE 
        va_list args;
        va_start(args, line);
        myprintfDx(format, args, filename, line);
        va_end(args);
    #endif
}

/**
*	@brief ����
*	@param value ����
*/
inline void DebugDx(const char* format, ...)
{
    #ifndef DEBUGDX_DISABLE 
        va_list args;
        va_start(args, format);
        myprintfDx(format, args);
        va_end(args);
    #endif
}



// ���b�Z�[�W�����p�֐�
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CDebugWindow {
public:
	CDebugWindow();
	~CDebugWindow();
	void Awake(HINSTANCE hInstance, HINSTANCE hPreInst, int nCmdShow);
	void Print(const char* format , ...);
	void PrintValue(const char* format,int value);
	void PrintValue(const char* format,float value);
	void PrintValue(const char* format,double value);
	void PrintJudge(bool flag, const char* format);
	void PrintKeyPush(int key, const char* format);
	void PrintKeyUp(int key, const char* format);
	void PrintKeyDown(int key, const char* format);
	void Loop();
	

private:
	HDC device;
	HWND hWnd;
	MSG msg;
	WNDCLASS myProg;
	std::vector<std::string> message;
	struct JudgeIn{
		std::string str;
		bool flag;
	};
	std::vector<JudgeIn> judge;

	int count;
};


}

extern suken::CDebugWindow debug;