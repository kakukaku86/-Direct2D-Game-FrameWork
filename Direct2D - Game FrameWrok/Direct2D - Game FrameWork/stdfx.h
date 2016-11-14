#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "Dwrite")

#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX 600
#define WINSIZEY 600

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }