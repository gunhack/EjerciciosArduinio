//KY016 3-color LED module
static const int RED_PIN = 9;
static const int GREEN_PIN = 10;
static const int BLUE_PIN = 11;

static const int RED_COLOR[3] = {0, 0, 255};
static const int GREEN_COLOR[3] = {0, 255, 0};
static const int BLUE_COLOR[3] = {255, 0, 0};
static const int WHITE_COLOR[3] = {255, 255, 255};
static const int OFF_COLOR[3] = {0, 0, 0};

static const int secuence[5] = {RED_COLOR, GREEN_COLOR, BLUE_COLOR, WHITE_COLOR, OFF_COLOR};

unsigned long startTime = 0, currentTime = 0;

int cont = 0;

void setup () {
  
  pinMode (RED_PIN, OUTPUT);
  pinMode (GREEN_PIN, OUTPUT);
  pinMode (BLUE_PIN, OUTPUT);

  startTime = millis();
}

void loop () {

  currentTime = millis() - startTime;

  if(currentTime >= 1000) {

    startTime = millis();
    cont ++;

    if(cont > 4) {
      cont = 0;
    }
  }

  showColor(secuence[cont]);
}

void showColor(int color[3]) {

  digitalWrite(RED_PIN, color[0]);
  digitalWrite(GREEN_PIN, color[1]);
  digitalWrite(BLUE_PIN, color[2]);
}
