# T-Displays
- Use platformino extension in VSCode, download the espressif32 6.6.0 through the extension
- All the screen related code is done under directory examples

# Red light on board for amoled
- You will have to press and hold the boot button (the one on the left), press the reset button, and finally release the boot button. Then, upload your code. If the red light is still showing, you might have to press the boot button or reset button (not sure which one but whichever one you press, it should show the green light after hopefully)
- If this doesn't work, make sure your com port is right. Also check through the extension to see if the board shows up under general > t-display > devices.

# Creating gifs for amoled
The board size is 240x536 (width x height). `TFT_HEIGHT` is 340px but this doesn't cover the entire height of the screen so do not use it. 536px is an estimate from my part but it covers the entire screen (calculated from 1.96" diagonal screen which is given on store page).
1) Due to the board's dimensions, you need to resize. Use [ezgif resize](https://ezgif.com/resize) while keeping the aspect ratio. If the background is not transparent, you need to add a background using GIMP; otherwise, you will have unmatched backgrounds. Assuming the background of the gif is only one solid color ie white, you should copy/move the resized gif to GIMP and you should see the frames as layers. For each layer, resize the layer boundary size and then add the matching background color. 
2) Use this [link](https://lvgl.io/tools/imageconverter) and select LVLGLv8. For color format, choose CF_RAW_CHROMA. For output, choose C array. Feel free to select and experiment with other options but these are what worked for me.

Note: The folders are cloned from [LilyGO](https://github.com/Xinyuan-LilyGO/T-Display-S3-AMOLED).
The only thing I modified/added was the GIFS folder to add gifs to the boards.
