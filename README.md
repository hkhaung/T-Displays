# T-Displays
- Use platformino extension in VSCode, download the espressif32 6.6.0 through the extension
- All the screen related code is done under directory examples

# Red light on board for amoled
- You will have to press and hold the boot button (the one on the left), press the reset button, and finally release the boot button. Then, upload your code. If the red light is still showing, you might have to press the boot button or reset button (not sure which one but whichever one you press, it should show the green light after hopefully)
- If this doesn't work, make sure your com port is right. Also check through the extension to see if the board shows up under general > t-display > devices.

# Creating gifs for amoled
- Use this [link](https://lvgl.io/tools/imageconverter) and select LVLGLv8. For color format, choose CF_RAW_CHROMA. For output, choose C array. Feel free to select and experiment with other options but these are what worked for me.
