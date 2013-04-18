#define bt Serial1
#define konsoll Serial


void setup()
{
  konsoll.begin(115200);
  bt.begin(115200);
  //delay(100);
  //bt.println("SQ,16");
}

void loop()
{
  if (bt.available()) {
    char c = bt.read();
    konsoll.print(c);
  }
  
  if (konsoll.available()) {
    char c = konsoll.read();
    bt.print(c);
  }
}
