package com.cooltrickshome;

import java.util.Scanner;

/**
 * http://www.kbdedit.com/manual/low_level_vk_list.html
 * Thanks to http://stackoverflow.com/questions/17419562/how-to-remap-keyboard-key-in-c-with-lowlevelkeyboardproc
 *
 */
public class RemapKeys {

private native void remapPassedKeys(int oldKey, int newKey);

static {
    System.loadLibrary("RemapKeys");
}

public static void main(String args[]) {
	
	final int oldKey; 
	final int newKey;
	
	Scanner s=new Scanner(System.in);
	System.out.println("Open helper.txt to get the keycodes");
	System.out.println("Enter the keycode for key to be remappped (For example type 42 if you want to remap b)");
	oldKey=s.nextInt(16);
	System.out.println("Enter the keycode for key to be remapped with");
	newKey=s.nextInt(16);
	s.close();
	Thread t = new Thread() 
	{ 
		public void run() {
		    RemapKeys o = new RemapKeys();
		    try {
		        o.remapPassedKeys(oldKey,newKey);
		    } catch(Exception exc) {
		        exc.printStackTrace();
		    }
		}
	};
	t.start();
	
	System.out.println("Sample Keyremapper started.");
	System.out.println("Do not use for any illegal purpose.");
	System.out.println("Exit the application to get back to normal");
	
}

}