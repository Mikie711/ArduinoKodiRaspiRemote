//
// compiled with Arduino 1.6.6
//
// keyboard does not work if debug mode is active !
//
/* autoResume.ino Example sketch for IRLib2
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
   Uses an external buffer in the auto resume feature.
*/
//This includes everything. Not generally recommended.
//It's better to include only the parts of library you really need.
//But for this example it's quick and easy. See "comboDump" example
//for a more efficient way.

//#define debug_mode

#define UPCODE     0x219EA05F
#define DOWNCODE   0x219E00FF
#define LEFTCODE   0x219EE01F
#define RIGHTCODE   0x219E906F
#define ENTERCODE   0x219E10EF
#define BACKCODE    0x219ED827
#define KEYPRESSTIM 100

#include "Keyboard.h"
// #include "IRLibAll.h" <=> keyboard does no longer work using following includes instead


#include <IRLibDecodeBase.h>
#include <IRLibSendBase.h>
#include <IRLib_P01_NEC.h>
#include <IRLib_P02_Sony.h>
#include <IRLib_P03_RC5.h>
#include <IRLib_P04_RC6.h>
#include <IRLib_P05_Panasonic_Old.h>
#include <IRLib_P06_JVC.h>
#include <IRLib_P07_NECx.h>
#include <IRLib_P08_Samsung36.h>
#include <IRLib_P09_GICable.h>
#include <IRLib_P10_DirecTV.h>
#include <IRLib_P11_RCMM.h>
// #include <IRLib_P12_CYKM.h>
// ^^^^ the include in the line above disables keyboard.h - but why ?
// it's the "keyboard mouse protocol" 
//include additional protocols here
#include <IRLibCombo.h>
#include <IRLibRecv.h>
#include <IRLibRecvLoop.h>
#include <IRLibRecvPCI.h>
#include <IRLibFreq.h>


IRrecvPCI myReceiver(2); //create receiver and pass pin number
IRdecode myDecoder;   //create decoder

//Create a buffer that we will use for decoding one stream while
//the receiver is using the default buffer "recvGlobal.recvBuffer"
uint16_t myBuffer[RECV_BUF_LENGTH];

void setup() 
{

#if defined debug_mode
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  Serial.println(F("Ready to receive IR signals"));
#else
  Keyboard.begin();
#endif

  myReceiver.enableAutoResume(myBuffer);   //Enable auto resume and pass it the address of your extra buffer
  myReceiver.enableIRIn(); // Start the receiver
  
}

void loop() {
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    myDecoder.decode();           //Decode it
    // myDecoder.dumpResults(false);  //Now print results. Use false for less detail
   
    // ********************************************************************************
  if (myDecoder.protocolNum == NEC) 
  {
    switch(myDecoder.value) 
      {
        case UPCODE:  
        {
        #if defined debug_mode
        Serial.println("up");
        #else
        Keyboard.press(KEY_UP_ARROW); delay(KEYPRESSTIM); Keyboard.releaseAll();
        #endif
        break;
        }

        case DOWNCODE:  
        {
        #if defined debug_mode
        Serial.println("down");
        #else
        Keyboard.press(KEY_DOWN_ARROW); delay(KEYPRESSTIM); Keyboard.releaseAll();
        #endif
        break;
        }

        case LEFTCODE:  
        {
        #if defined debug_mode
        Serial.println("left");
        #else
        Keyboard.press(KEY_LEFT_ARROW); delay(KEYPRESSTIM); Keyboard.releaseAll();
        #endif
        break;
        }

        case RIGHTCODE:  
        {
        #if defined debug_mode
        Serial.println("right");
        #else
        Keyboard.press(KEY_RIGHT_ARROW); delay(KEYPRESSTIM); Keyboard.releaseAll();
        #endif
        break;
        }

        case ENTERCODE:  
        {
        #if defined debug_mode
        Serial.println("enter");
        #else
        Keyboard.press(KEY_RETURN); delay(KEYPRESSTIM); Keyboard.releaseAll();
        #endif
        break;
        }

        case BACKCODE:  
        {
        #if defined debug_mode
        Serial.println("back");
        #else
        Keyboard.press(KEY_ESC); delay(KEYPRESSTIM); Keyboard.releaseAll();
        #endif
        break;
        }

        case 0xffffffff:  //repeat
          // do nothing
          break;
          
      }

        #if defined debug_mode
        Serial.print(" protocolNum:");
        Serial.print(myDecoder.protocolNum, HEX);
        Serial.print(" value: ");
        Serial.println(myDecoder.value, HEX);
        #else
        #endif


    
  }
  else
  {
    #if defined debug_mode
    Serial.print(" protocolNum:");
    Serial.print(myDecoder.protocolNum, HEX);
    Serial.print(" value: ");
    Serial.println(myDecoder.value, HEX);
    #endif
  }
 // ********************************************************************************    
    myReceiver.enableIRIn();      //Restart receiver
  }
}



