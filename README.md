# phonewave-decoder
DTMF-to-microwave decoder for the Phonewave (made at MakeUofT 2022)

Code based on [a project by MM_Shoaib published on Arduino Project Hub](https://create.arduino.cc/projecthub/MM_Shoaib/dtmf-decoder-using-only-arduino-872502).
Modifications made to adjust sensitivity for hardware setup and to improve readability.

## Setup

1. Install the Arduino IDE, CLI, or a tool of your choice.
2. Open the decoder file.
3. Download [the Goertzel algorithm library](https://github.com/jacobrosenthal/Goertzel).
4. Include the library in your IDE.
  - In the Arduino IDE, this is under `Sketch > Include Library > Add .ZIP library`.
5. Upload the code to your Arduino board.
  - Tested with an Arduino Uno. You may have to adjust sensitivity for your specific hardware.
