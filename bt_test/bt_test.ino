#define bluetooth Serial1
#define konsoll Serial

void setup()
{
  konsoll.begin(115200);
  bluetooth.begin(115200);

  delay(100);
  bluetooth.println("SQ,16");
}

void loop()
{
  if (bluetooth.available()) {
    konsoll.print((char)bluetooth.read());
  }
  
  if (konsoll.available()) {
    //konsoll.println("Konsoll skickar:");
    bluetooth.print((char)konsoll.read());
  }
}
