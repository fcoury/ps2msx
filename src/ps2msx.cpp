#include <Arduino.h>
#include <hidboot.h>
#include <usbhub.h>
#include "ps2dev.h" // to emulate a PS/2 device

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

const int DataPin = 2;
const int ClkPin = 3;
const int LedPin = 13;

PS2dev keyboard(ClkPin, DataPin); // PS2dev object (2:data, 3:clock)
int enabled = 0; // pseudo variable for state of "keyboard"

void kbSend(uint8_t key)
{
  Serial.print("Sending ");
  Serial.println(key, HEX);
  keyboard.write(key);
}

class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown	(uint8_t mod, uint8_t key);
    void OnKeyUp	(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
  MODIFIERKEYS mod;
  *((uint8_t*)&mod) = m;
  Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
  Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
  Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");

  Serial.print(" >");
  PrintHex<uint8_t>(key, 0x80);
  Serial.print("< ");

  Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
  Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
  Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
  Serial.println((mod.bmRightGUI    == 1) ? "G" : " ");
};

// --- (AUTOGEN START) ---
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  Serial.print("Down ");
  Serial.println(key, HEX);

  Serial.print("DN ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  Serial.print("ASCII: ");
  Serial.println((char)key);

  switch(key) {
  case 0x29: // esc
    kbSend(0x76);
    break;

  case 0x3a: // f1
    kbSend(0x05);
    break;

  case 0x3b: // f2
    kbSend(0x06);
    break;

  case 0x3c: // f3
    kbSend(0x04);
    break;

  case 0x3d: // f4
    kbSend(0x0c);
    break;

  case 0x3e: // f5
    kbSend(0x03);
    break;

  case 0x3f: // f6
    kbSend(0x0b);
    break;

  case 0x40: // f7
    kbSend(0x83);
    break;

  case 0x41: // f8
    kbSend(0x0a);
    break;

  case 0x42: // f9
    kbSend(0x01);
    break;

  case 0x43: // f10
    kbSend(0x09);
    break;

  case 0x44: // f11
    kbSend(0x78);
    break;

  case 0x45: // f12
    kbSend(0x07);
    break;

  case 0x46: // print_screen
    kbSend(0xe0);
    kbSend(0x12);
    kbSend(0xe0);
    kbSend(0x7c);
    break;

  case 0x47: // scroll_lock
    kbSend(0x7e);
    break;

  case 0x48: // pause
    kbSend(0xe1);
    kbSend(0x14);
    kbSend(0x77);
    kbSend(0xe1);
    kbSend(0xf0);
    kbSend(0x14);
    kbSend(0xe0);
    kbSend(0x77);
    break;

  case 0x49: // insert
    kbSend(0xe0);
    kbSend(0x70);
    break;

  case 0x4a: // home
    kbSend(0xe0);
    kbSend(0x6c);
    break;

  case 0x4b: // page_up
    kbSend(0xe0);
    kbSend(0x7d);
    break;

  case 0x4c: // delete
    kbSend(0xe0);
    kbSend(0x71);
    break;

  case 0x4d: // end
    kbSend(0xe0);
    kbSend(0x69);
    break;

  case 0x4e: // page_down
    kbSend(0xe0);
    kbSend(0x7a);
    break;

  case 0x35: // `
    kbSend(0x0e);
    break;

  case 0x1e: // 1
    kbSend(0x16);
    break;

  case 0x1f: // 2
    kbSend(0x1e);
    break;

  case 0x20: // 3
    kbSend(0x26);
    break;

  case 0x21: // 4
    kbSend(0x25);
    break;

  case 0x22: // 5
    kbSend(0x2e);
    break;

  case 0x23: // 6
    kbSend(0x36);
    break;

  case 0x24: // 7
    kbSend(0x3d);
    break;

  case 0x25: // 8
    kbSend(0x3e);
    break;

  case 0x26: // 9
    kbSend(0x46);
    break;

  case 0x27: // 0
    kbSend(0x45);
    break;

  case 0x2d: // -
    kbSend(0x4e);
    break;

  case 0x2e: // =
    kbSend(0x55);
    break;

  case 0x2a: // backspace
    kbSend(0x66);
    break;

  case 0x2b: // tab
    kbSend(0x0d);
    break;

  case 0x14: // q
    kbSend(0x15);
    break;

  case 0x1a: // w
    kbSend(0x1d);
    break;

  case 0x08: // e
    kbSend(0x24);
    break;

  case 0x15: // r
    kbSend(0x2d);
    break;

  case 0x17: // t
    kbSend(0x2c);
    break;

  case 0x1c: // y
    kbSend(0x35);
    break;

  case 0x18: // u
    kbSend(0x3c);
    break;

  case 0x0c: // i
    kbSend(0x43);
    break;

  case 0x12: // o
    kbSend(0x44);
    break;

  case 0x13: // p
    kbSend(0x4d);
    break;

  case 0x2f: // [
    kbSend(0x54);
    break;

  case 0x30: // ]
    kbSend(0x5b);
    break;

  case 0x31: // \\
    kbSend(0x5d);
    break;

  case 0x39: // caps_lock
    kbSend(0x58);
    break;

  case 0x04: // a
    kbSend(0x1c);
    break;

  case 0x16: // s
    kbSend(0x1b);
    break;

  case 0x07: // d
    kbSend(0x23);
    break;

  case 0x09: // f
    kbSend(0x2b);
    break;

  case 0x0a: // g
    kbSend(0x34);
    break;

  case 0x0b: // h
    kbSend(0x33);
    break;

  case 0x0d: // j
    kbSend(0x3b);
    break;

  case 0x0e: // k
    kbSend(0x42);
    break;

  case 0x0f: // l
    kbSend(0x4b);
    break;

  case 0x33: // ;
    kbSend(0x4c);
    break;

  case 0x34: // '
    kbSend(0x52);
    break;

  case 0x28: // enter
    kbSend(0x5a);
    break;

  case 0x1d: // z
    kbSend(0x1a);
    break;

  case 0x1b: // x
    kbSend(0x22);
    break;

  case 0x06: // c
    kbSend(0x21);
    break;

  case 0x19: // v
    kbSend(0x2a);
    break;

  case 0x05: // b
    kbSend(0x32);
    break;

  case 0x11: // n
    kbSend(0x31);
    break;

  case 0x10: // m
    kbSend(0x3a);
    break;

  case 0x36: // ,
    kbSend(0x41);
    break;

  case 0x37: // .
    kbSend(0x49);
    break;

  case 0x38: // num_slash
    kbSend(0xe0);
    kbSend(0x4a);
    break;

  case 0x2c: // space
    kbSend(0x29);
    break;

  case 0x52: // up
    kbSend(0xe0);
    kbSend(0x75);
    break;

  case 0x50: // left
    kbSend(0xe0);
    kbSend(0x6b);
    break;

  case 0x51: // down
    kbSend(0xe0);
    kbSend(0x72);
    break;

  case 0x4f: // right
    kbSend(0xe0);
    kbSend(0x74);
    break;

  }
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.print("Up ");
  Serial.println(key, HEX);

  Serial.print("UP ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  Serial.print("ASCII: ");
  Serial.println((char)key);

  switch(key) {
  case 0x29: // esc
    kbSend(0xf0);
    kbSend(0x76);
    break;

  case 0x3a: // f1
    kbSend(0xf0);
    kbSend(0x05);
    break;

  case 0x3b: // f2
    kbSend(0xf0);
    kbSend(0x06);
    break;

  case 0x3c: // f3
    kbSend(0xf0);
    kbSend(0x04);
    break;

  case 0x3d: // f4
    kbSend(0xf0);
    kbSend(0x0c);
    break;

  case 0x3e: // f5
    kbSend(0xf0);
    kbSend(0x03);
    break;

  case 0x3f: // f6
    kbSend(0xf0);
    kbSend(0x0b);
    break;

  case 0x40: // f7
    kbSend(0xf0);
    kbSend(0x83);
    break;

  case 0x41: // f8
    kbSend(0xf0);
    kbSend(0x0a);
    break;

  case 0x42: // f9
    kbSend(0xf0);
    kbSend(0x01);
    break;

  case 0x43: // f10
    kbSend(0xf0);
    kbSend(0x09);
    break;

  case 0x44: // f11
    kbSend(0xf0);
    kbSend(0x78);
    break;

  case 0x45: // f12
    kbSend(0xf0);
    kbSend(0x07);
    break;

  case 0x46: // print_screen
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x7c);
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x12);
    break;

  case 0x47: // scroll_lock
    kbSend(0xf0);
    kbSend(0x7e);
    break;

  case 0x48: // pause

    break;

  case 0x49: // insert
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x70);
    break;

  case 0x4a: // home
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x6c);
    break;

  case 0x4b: // page_up
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x7d);
    break;

  case 0x4c: // delete
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x71);
    break;

  case 0x4d: // end
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x69);
    break;

  case 0x4e: // page_down
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x7a);
    break;

  case 0x35: // `
    kbSend(0xf0);
    kbSend(0x0e);
    break;

  case 0x1e: // 1
    kbSend(0xf0);
    kbSend(0x16);
    break;

  case 0x1f: // 2
    kbSend(0xf0);
    kbSend(0x1e);
    break;

  case 0x20: // 3
    kbSend(0xf0);
    kbSend(0x26);
    break;

  case 0x21: // 4
    kbSend(0xf0);
    kbSend(0x25);
    break;

  case 0x22: // 5
    kbSend(0xf0);
    kbSend(0x2e);
    break;

  case 0x23: // 6
    kbSend(0xf0);
    kbSend(0x36);
    break;

  case 0x24: // 7
    kbSend(0xf0);
    kbSend(0x3d);
    break;

  case 0x25: // 8
    kbSend(0xf0);
    kbSend(0x3e);
    break;

  case 0x26: // 9
    kbSend(0xf0);
    kbSend(0x46);
    break;

  case 0x27: // 0
    kbSend(0xf0);
    kbSend(0x45);
    break;

  case 0x2d: // -
    kbSend(0xf0);
    kbSend(0x4e);
    break;

  case 0x2e: // =
    kbSend(0xf0);
    kbSend(0x55);
    break;

  case 0x2a: // backspace
    kbSend(0xf0);
    kbSend(0x66);
    break;

  case 0x2b: // tab
    kbSend(0xf0);
    kbSend(0x0d);
    break;

  case 0x14: // q
    kbSend(0xf0);
    kbSend(0x15);
    break;

  case 0x1a: // w
    kbSend(0xf0);
    kbSend(0x1d);
    break;

  case 0x08: // e
    kbSend(0xf0);
    kbSend(0x24);
    break;

  case 0x15: // r
    kbSend(0xf0);
    kbSend(0x2d);
    break;

  case 0x17: // t
    kbSend(0xf0);
    kbSend(0x2c);
    break;

  case 0x1c: // y
    kbSend(0xf0);
    kbSend(0x35);
    break;

  case 0x18: // u
    kbSend(0xf0);
    kbSend(0x3c);
    break;

  case 0x0c: // i
    kbSend(0xf0);
    kbSend(0x43);
    break;

  case 0x12: // o
    kbSend(0xf0);
    kbSend(0x44);
    break;

  case 0x13: // p
    kbSend(0xf0);
    kbSend(0x4d);
    break;

  case 0x2f: // [
    kbSend(0xf0);
    kbSend(0x54);
    break;

  case 0x30: // ]
    kbSend(0xf0);
    kbSend(0x5b);
    break;

  case 0x31: // \\
    kbSend(0xf0);
    kbSend(0x5d);
    break;

  case 0x39: // caps_lock
    kbSend(0xf0);
    kbSend(0x58);
    break;

  case 0x04: // a
    kbSend(0xf0);
    kbSend(0x1c);
    break;

  case 0x16: // s
    kbSend(0xf0);
    kbSend(0x1b);
    break;

  case 0x07: // d
    kbSend(0xf0);
    kbSend(0x23);
    break;

  case 0x09: // f
    kbSend(0xf0);
    kbSend(0x2b);
    break;

  case 0x0a: // g
    kbSend(0xf0);
    kbSend(0x34);
    break;

  case 0x0b: // h
    kbSend(0xf0);
    kbSend(0x33);
    break;

  case 0x0d: // j
    kbSend(0xf0);
    kbSend(0x3b);
    break;

  case 0x0e: // k
    kbSend(0xf0);
    kbSend(0x42);
    break;

  case 0x0f: // l
    kbSend(0xf0);
    kbSend(0x4b);
    break;

  case 0x33: // ;
    kbSend(0xf0);
    kbSend(0x4c);
    break;

  case 0x34: // '
    kbSend(0xf0);
    kbSend(0x52);
    break;

  case 0x28: // enter
    kbSend(0xf0);
    kbSend(0x5a);
    break;

  case 0x1d: // z
    kbSend(0xf0);
    kbSend(0x1a);
    break;

  case 0x1b: // x
    kbSend(0xf0);
    kbSend(0x22);
    break;

  case 0x06: // c
    kbSend(0xf0);
    kbSend(0x21);
    break;

  case 0x19: // v
    kbSend(0xf0);
    kbSend(0x2a);
    break;

  case 0x05: // b
    kbSend(0xf0);
    kbSend(0x32);
    break;

  case 0x11: // n
    kbSend(0xf0);
    kbSend(0x31);
    break;

  case 0x10: // m
    kbSend(0xf0);
    kbSend(0x3a);
    break;

  case 0x36: // ,
    kbSend(0xf0);
    kbSend(0x41);
    break;

  case 0x37: // .
    kbSend(0xf0);
    kbSend(0x49);
    break;

  case 0x38: // num_slash
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x4a);
    break;

  case 0x2c: // space
    kbSend(0xf0);
    kbSend(0x29);
    break;

  case 0x52: // up
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x75);
    break;

  case 0x50: // left
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x6b);
    break;

  case 0x51: // down
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x72);
    break;

  case 0x4f: // right
    kbSend(0xe0);
    kbSend(0xf0);
    kbSend(0x74);
    break;

  }
}
// --- (AUTOGEN END) ---

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    Serial.print("LeftCtrl changed - ");
    Serial.println(afterMod.bmLeftCtrl ? "on" : "off");
    if (afterMod.bmLeftCtrl) {
      kbSend(0x14);
    } else {
      kbSend(0xf0);
      kbSend(0x14);
    }
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    Serial.print("LeftShift changed - ");
    Serial.println(afterMod.bmLeftShift ? "on" : "off");
    if (afterMod.bmLeftShift) {
      kbSend(0x12);
    } else {
      kbSend(0xf0);
      kbSend(0x12);
    }
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    Serial.print("LeftAlt changed - ");
    Serial.println(afterMod.bmLeftAlt ? "on" : "off");
    if (afterMod.bmLeftAlt) {
      kbSend(0x11);
    } else {
      kbSend(0xf0);
      kbSend(0x11);
    }
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    Serial.print("LeftGUI changed - ");
    Serial.println(afterMod.bmLeftGUI ? "on" : "off");
    if (afterMod.bmLeftGUI) {
      kbSend(0xe0);
      kbSend(0x1f);
    } else {
      kbSend(0xe0);
      kbSend(0xf0);
      kbSend(0x1f);
    }
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    Serial.print("RightCtrl changed - ");
    Serial.println(afterMod.bmRightCtrl ? "on" : "off");
    if (afterMod.bmRightCtrl) {
      kbSend(0xe0);
      kbSend(0x14);
    } else {
      kbSend(0xe0);
      kbSend(0xf0);
      kbSend(0x14);
    }
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    Serial.println(afterMod.bmRightShift ? "on" : "off");
    if (afterMod.bmRightShift) {
      kbSend(0x59);
    } else {
      kbSend(0xf0);
      kbSend(0x59);
    }
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    Serial.print("RightAlt changed - ");
    Serial.println(afterMod.bmRightAlt ? "on" : "off");
    if (afterMod.bmRightAlt) {
      kbSend(0xe0);
      kbSend(0x11);
    } else {
      kbSend(0xe0);
      kbSend(0xf0);
      kbSend(0x11);
    }
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    Serial.print("RightGUI changed - ");
    Serial.println(afterMod.bmRightGUI ? "on" : "off");
    if (afterMod.bmRightGUI) {
      kbSend(0xe0);
      kbSend(0x27);
    } else {
      kbSend(0xe0);
      kbSend(0xf0);
      kbSend(0x27);
    }
  }

}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
  Serial.print("ASCII: ");
  Serial.println((char)key);
};

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

void ack() {
  //acknowledge commands
  while(keyboard.write(0xFA));
}

void kbdCmd(int command) {
  unsigned char val;
  Serial.print("Rcv: 0x");
  Serial.println(command, HEX);
  switch (command) {
  case 0xFF: //reset
    ack();
    //the while loop lets us wait for the host to be ready
    while(keyboard.write(0xAA)!=0);
    break;
  case 0xFE: //resend
    ack();
    break;
  case 0xF6: //set defaults
    //enter stream mode
    ack();
    break;
  case 0xF5: //disable data reporting
    //FM
    enabled = 0;
    ack();
    break;
  case 0xF4: //enable data reporting
    //FM
    enabled = 1;
    ack();
    break;
  case 0xF3: //set typematic rate
    ack();
    keyboard.read(&val); //do nothing with the rate
    ack();
    break;
  case 0xF2: //get device id
    ack();
    keyboard.write(0xAB);
    keyboard.write(0x83);
    break;
  case 0xF0: //set scan code set
    ack();
    keyboard.read(&val); //do nothing with the rate
    ack();
    break;
  case 0xEE: //echo
    //ack();
    keyboard.write(0xEE);
    break;
  case 0xED: //set/reset LEDs
    ack();
    keyboard.read(&val); //do nothing with the rate
    ack();
    break;
  }
}

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);

  pinMode(LedPin, OUTPUT);

  keyboard.write(0xAA);
  Serial.println("Output Connected");
  delay(100);

//  connectHost();
  Serial.println("\nSerial Host Connected");
  Serial.flush();
}

void loop()
{
  Usb.Task();

  if( (digitalRead(ClkPin)==LOW) || (digitalRead(DataPin) == LOW)) {
    if(digitalRead(ClkPin)==LOW){
      Serial.println("Clock is LOW");
    } else {
      Serial.println("Data is LOW");
    }
    unsigned char c;
    while(keyboard.read(&c));
    kbdCmd(c);
    Serial.print("Target: 0x");
    Serial.println(c, HEX);
  }
}
