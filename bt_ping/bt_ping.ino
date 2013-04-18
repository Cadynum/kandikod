#define bluetooth Serial2
#define konsoll Serial

void setup()
{
  konsoll.begin(115200);
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("SQ,16");
}

void loop()
{
  if (bluetooth.available()) {
    byte chr = bluetooth.read();
    bluetooth.write(chr);
  }
}
