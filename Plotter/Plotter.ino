/**
 * Copyright (c) Art Hackers, 2012 under the terms and conditions
 *               of the Expat license. Individual copyright holders
 *               are listed below.
 *
 *     - Paul Tagliamonte <tag@pault.ag>
 */

int x_pin = 11;
int y_pin = 10;

float x_location = 0;
float y_location = 0;


void setup() {
  pinMode(x_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  Serial.begin(14400);
}


void move_to(int x_loc, int y_loc) {
  float delta_x = x_loc - x_location;
  float delta_y = y_loc - y_location;
  
  int steps = abs(delta_x);
  if ( abs(delta_y) > steps ) {
    steps = abs(delta_y);
  }

  float x_step = (delta_x / steps);
  float y_step = (delta_y / steps);
  
  Serial.println("Debug: dX dY sX sY s");
  Serial.print(delta_x);
  Serial.print(" ");
  Serial.print(delta_y);
  Serial.print(" ");
  Serial.print(x_step);
  Serial.print(" ");
  Serial.print(y_step);
  Serial.print(" ");
  Serial.println(steps);
  
  for ( int i = 0; i < steps; ++i ) {
    x_location += x_step;
    y_location += y_step;
    update_ptr();
    delay(10);
  }
}


void update_ptr() {
  analogWrite(x_pin, x_location);
  analogWrite(y_pin, y_location); 
}


void loop() {
  while (Serial.available() > 0) {
    Serial.println("Waiting on Serial.");
    while(Serial.read() != ':');
    int next_x = Serial.parseInt();
    int next_y = Serial.parseInt();
    if (Serial.read() == '\n') {
      move_to(next_x, next_y);
    }
   
  }
  update_ptr();
}

