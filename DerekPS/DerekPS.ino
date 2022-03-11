#define IN_PIN A0
#define WINDOW_SIZE 5

#define VSAMPLE_SIZE 40

int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

int vIndex = 0;
// shared value
int vReadings[VSAMPLE_SIZE];
long vSum = 0;
int vAverage = 0;
long variance;

bool pressed = false;

void setup() {
  pinMode(IN_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {

  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = analogRead(IN_PIN);        // Read the next sensor value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX + 1) % WINDOW_SIZE; // Increment the index, and wrap to 0 if it exceeds the window size
  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result

  vSum -= vReadings[vIndex];
  vReadings[vIndex] = VALUE;
  vSum += VALUE;
  vIndex = (vIndex + 1) % VSAMPLE_SIZE;
  vAverage = vSum / VSAMPLE_SIZE;

  variance = 0;
  for (int i = 0; i < VSAMPLE_SIZE; i++) {
    variance += sq((vReadings[i] - vAverage ) / 10);
  }
  variance /= (VSAMPLE_SIZE);

  pressed = variance > 20 && variance < 500;

  if(pressed)
  Serial.print(500);
  else
  Serial.print(20);

  Serial.print(",");
  Serial.print(VALUE);
  Serial.print(",");
  Serial.print(AVERAGED);
  Serial.print(",");
  Serial.println(vAverage);
  // Serial.println(constrain(variance,0,1000));

  delay(25);
}
