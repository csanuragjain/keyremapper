#include <stdio.h>
#include <windows.h>
#include <w32api.h>
#include "RemapKeys.h"

static HHOOK handleKeyboardHook = NULL;
HINSTANCE hInst = NULL;
DWORD oldKey=NULL;
DWORD newKey=NULL;

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
      
	if (nCode == HC_ACTION)
    	{
        	KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*) lParam;
        	if (p->vkCode == oldKey) 
        		{
           			switch (wParam){

            						case WM_KEYDOWN :{ 
                					keybd_event(newKey, 0x1D, KEYEVENTF_EXTENDEDKEY | 0, 0 );
	            					break;
            										}
   
            						case WM_KEYUP:{
	                				keybd_event(newKey, 0x1D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
						            break;
             										}
           
		   							default:
                					wParam = WM_SYSKEYDOWN; 
                					break;
           							}
            		return 1;
        		}
    	}	
  	return CallNextHookEx(handleKeyboardHook, nCode, wParam, lParam);
}

JNIEXPORT void JNICALL Java_com_cooltrickshome_RemapKeys_remapPassedKeys
  (JNIEnv *, jobject, jint oldValue, jint newValue) {
  	
  	 /* printf("Your message here\n");
  		fflush(stdout);*/
  		
	oldKey=oldValue;
  	newKey=newValue;
  	
	hInst = GetModuleHandle(NULL);
	handleKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc,hInst, 0);
  	
	MSG msg;
  	while(GetMessage(&msg, NULL, 0, 0))
  	{
    	TranslateMessage(&msg);
    	DispatchMessage(&msg);
  	}	 
}

