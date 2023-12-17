
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// Hardware SPI connection
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


#define SPEED_TIME  20
#define PAUSE_TIME  1500

// Turn on debug statements to the serial output
#define  DEBUG  0

#if  DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

// Global variables
uint8_t  curText;
const char  *pc[] =
{
  "Auguri",
  "Buone",
  "Feste",
  "DA",
  "Pasq.",
  "LAB"
};

uint8_t  inFX, outFX;
textEffect_t  effect[] =
{
  PA_PRINT,             //0
  PA_SCAN_HORIZ,        //1
  PA_SCROLL_LEFT,       //2
  PA_WIPE,              //3
  PA_SCROLL_UP_LEFT,    //4
  PA_SCROLL_UP,         //5
  PA_OPENING_CURSOR,    //6
  PA_GROW_UP,           //7
  PA_MESH,              //8
  PA_SCROLL_UP_RIGHT,   //9
  PA_BLINDS,            //10
  PA_CLOSING,           //11
  PA_RANDOM,            //12
  PA_GROW_DOWN,         //13
  PA_SCAN_VERT,         //14
  PA_SCROLL_DOWN_LEFT,  //15
  PA_WIPE_CURSOR,       //16
  PA_DISSOLVE,          //17
  PA_OPENING,           //18
  PA_CLOSING_CURSOR,    //19
  PA_SCROLL_DOWN_RIGHT, //20
  PA_SCROLL_RIGHT,      //21
  PA_SLICE,             //22
  PA_SCROLL_DOWN,       //23
};



void setup(void)
{
  Serial.begin(115200);
  PRINTS("[Parola Demo]");

  P.begin();
  P.setInvert(false);
  P.displayText(pc[curText], PA_CENTER, SPEED_TIME, PAUSE_TIME, effect[inFX], effect[outFX]);
}

void loop(void)
{


  if (P.displayAnimate()) // animates and returns true when an animation is completed
  {
    // Set the display for the next string.
    curText = (curText + 1) % ARRAY_SIZE(pc);
    P.setTextBuffer(pc[curText]);

    switch(curText)
    {
      case 0:
        P.setTextEffect(effect[3], effect[5]);  //Auguri
        break;

      case 1:
        P.setTextEffect(effect[12], effect[2]);  //Buone
        break;

      case 2:
        P.setTextEffect(effect[10], effect[21]);  //Feste
        break;

      case 3:
        P.setTextEffect(effect[16], effect[17]);   //Da
        break;

      case 4:
        P.setTextEffect(effect[8], effect[22]);   //Pas...
        break; 

      case 5:
        P.setTextEffect(effect[18], effect[23]);   //LAB
        break; 

      default:
        break;          
    }
    

     
    // Tell Parola we have a new animation
    P.displayReset();
  }
}
