#define REDPIN 2 //red 模拟量
#define GREENPIN 0 //green 模拟量
#define BLUEPIN 4 //blue 模拟量

long colorNum = -19456;// RGB颜色对应的数字：-1 到 -16777216

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  Serial.println(int2rgb(-1, ""));
  Serial.println(rgb2int("255", "255", "255"));
  Serial.println(int2rgb(-16777216, ""));
  Serial.println(rgb2int("0", "0", "0"));
  Serial.println(int2rgb(-19456, ""));
  Serial.println(rgb2int("255", "180", "0"));
}

void loop() {

  testColor();// 颜色校正

  setColorByNum(colorNum);

  delay(2000);
}

// ***共阴RGB*** - 设置RGB三色，参数范围：0-255
void setColor(int red, int green, int blue)
{
  analogWrite(REDPIN, red);
  analogWrite(GREENPIN, green);
  analogWrite(BLUEPIN, blue);
}

//// ***共阳RGB*** - 设置RGB三色，参数范围：0-255
//void setColor(int red, int green, int blue)
//{
//  analogWrite(REDPIN, 255-red);
//  analogWrite(GREENPIN, 255-green);
//  analogWrite(BLUEPIN, 255-blue);
//}

// 根据颜色对应的数值设置RGB三色
void setColorByNum(long num)
{
  String r = int2rgb(num, "r");
  String g = int2rgb(num, "g");
  String b = int2rgb(num, "b");
  int r2 = r.toInt();
  int g2 = g.toInt();
  int b2 = b.toInt();
  setColor(r2, g2, b2);
}

// 数字转成rgb字符串
String int2rgb(long int i, String flag) {
  long int r = (i & 0xff0000) >> 16;
  long int g = (i & 0xff00) >> 8;
  long int b = (i & 0xff);
  if(flag == "r") return String(r);
  if(flag == "g") return String(g);
  if(flag == "b") return String(b);
  return String(r) + "," + String(g) + "," + String(b);
}

// rgb转数字
long int rgb2int(String r, String g, String b) {
  long int r2 = r.toInt();
  long int g2 = g.toInt();
  long int b2 = b.toInt();
  long int color = ((0xff << 24) | (r2 << 16) | (g2 << 8) | b2);
  color = color - 16777216;
  return color;
}


// 颜色校正函数
void testColor()
{
  setColor(255, 0, 0); //Red
  Serial.println("RED");
  delay(2000);
  setColor(0, 255, 0); //Green
  Serial.println("GREEN");
  delay(2000);
  setColor(0, 0, 255); //blue
  Serial.println("BLUE");
  delay(2000);
  setColor(135, 206, 250); //
  Serial.println("LightSkyBlue");
  delay(2000);
  setColor(0, 255, 255); //
  Serial.println("Cyan");
  delay(2000);
  setColor(255, 215, 0); //
  Serial.println("Gold");
  delay(2000);
}
