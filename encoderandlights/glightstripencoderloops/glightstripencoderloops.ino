if (-50 < encodervelocity < -40) {
      strip.setPixelColor(i, 0, 40, 188);
    //strip.setPixelColor(1, 0, 255, 0);
    strip.show();
      }
     if (-40 < encodervelocity < -30) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      } 
      if (-30 < encodervelocity < -20) {
      strip.setPixelColor(i, 97, 192, 255);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      } 
      if (-20 < encodervelocity < -10) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      } 
      if (-10 < encodervelocity < 0) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      } 
      if (0 < encodervelocity < 10) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      }
      if (10 < encodervelocity < 20) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      }  
      if (20 < encodervelocity < 30) {
      strip.setPixelColor(i, 184, 232, 30);
    strip.show();
      } 
      if (30 < encodervelocity < 40) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      } 
      if (40 < encodervelocity < 50) {
      strip.setPixelColor(i, 184, 232, 30);
    //strip.setPixelColor(1, 255, 0, 0);
    strip.show();
      } 
    //Serial.println(lastposition);
