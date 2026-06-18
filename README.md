Wiring
ESP32C3
Oled GND Vcc 5v Pin 7 SDA and Pin 6 SCL.
Sound Sensor GND Vcc 3.3v Pin 2 

perlin.h and perlin.cpp:
These files contain the implementation of the Perlin noise algorithm. perlin.h declares the functions, and perlin.cpp defines them. The most important function is noise3d(x, y, z), which generates a pseudo-random value between -1 and 1 based on the 3D coordinates x, y, and z. The p array is a permutation table used in the Perlin noise calculation. The fade, lerp and grad functions are helper functions used by noise3d.


• 3D Perlin Noise: Uses noise3d() for a true 3D effect. The zOff parameter controls the "depth" of the wave.
• Sound Interaction: 
o Reads the sound sensor value.
o Calculates the sound level relative to a soundBaseline (important for handling ambient noise). You must calibrate this. Find a quiet room, read the sensor, and that's your baseline.
o Maps the sound level to the zOff of the Perlin noise. A louder sound will influence the wave more.
o Decay: zOff *= 0.95; This line adds a decay to the sound influence. The wave disturbed by sound will gradually return to its original state. This makes the interaction feel more natural. Adjust the 0.95 value to change the decay rate.
• Sound Calibration: The code now includes soundThreshold and soundBaseline. You absolutely must calibrate these for your environment. The easiest way to do this is to print the soundValue to the Serial Monitor and observe the range of values in a quiet room and when you make a sound.
• Smoother Wave (Optional): The code includes drawing lines between the calculated points to create a smoother wave. This is commented out by default. Uncomment the display.drawLine() lines and the y_prev and y2_prev declarations if you want the smoother look.
• Mapping and Scaling: Uses map() to scale the Perlin noise output to the OLED display's height and the sound level to the zOff range. Adjust the mapping values to fine-tune the visualization.
• Animation: The xOff and yOff values are incremented to animate the wave.
• Clearer Comments: More comments to explain the code.
• Includes: Added necessary includes for Perlin noise and the OLED display.
How to Use:
1. Hardware: Connect your ESP32, OLED display, and sound sensor (e.g., KY-038) according to the pin definitions in the code. The sound sensor's analog output goes to the SOUND_PIN.
2. Libraries: Install the Adafruit_GFX, Adafruit_SSD1306, and Perlin libraries in the Arduino IDE.
3. Calibration: This is crucial. Open the Serial Monitor. In a quiet environment, note the readings from the sound sensor. This is your soundBaseline. Then, make a sound and note the highest value. Use these values to set soundBaseline and adjust the mapping in the code.
4. Upload: Upload the code to your ESP32.
5. Adjust: Experiment with the Perlin noise parameters, sound mapping values, and decay rate to achieve the desired visual effect. The mapping of the sound to zOff is particularly important to get right.
This revised code provides a much more interactive and visually appealing 3D-like Perlin wave that responds to sound input. Remember to calibrate the sound sensor for your specific environment!
