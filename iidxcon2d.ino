#include <Bounce2.h> 
int d=0, c=0;
Bounce  key[10] = {{0,d},{1,d},{2,d},{3,d},{4,d},{5,d},{6,d},{7,d},{8,d},{9,d}}; 

class Turntable{
  private:
  bool up, up2, o=0, n=1, q=0, p=1, still, wasstill;
  float debounce;
  int c2=0;
  public:
  void update(void){
    n = digitalReadFast(22);
    p = digitalReadFast(23);
    if ((q==1) && (p==0)) {
      if (digitalRead(22)){ c2++; if (c2>2){up=true;/*Mouse.move(0,1);*/c2=0;}}
      else { c2--; if(c2<-2){up=false;/*Mouse.move(0,-1);*/c2=0;}}
      still=false;c=0;}
      if ((p==q)&&(n==o)&&(c>1000)){c=0; still=true;}
      if (wasstill && !still) Keyboard.press('j'+up);
      if (still){ Keyboard.release('j'+up); Keyboard.release('j'); }
      if ((up2!=up)&&(c>200)){ Keyboard.release('k'-up); Keyboard.press('j'+up); c=0; }
      q=p; o=n; up2=up; wasstill=still; c++;}};

Turntable turntable;
 
void setup() {
  for (int i=0; i<10; i++) pinMode(i, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP); pinMode(23,  INPUT_PULLUP);
}

void loop() {  
  for(int i=0; i<10; i++) {
    key[i].update();
    if (key[i].fell()) Keyboard.press('a'+i);
    if (key[i].rose()) Keyboard.release('a'+i);
  }
  turntable.update();
}
