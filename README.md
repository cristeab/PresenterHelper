                            Presenter Helper

                        author: Bogdan Cristea
                        e-mail: cristeab@gmail.com
   Presenter Helper aims at replacing the laser pointer used in presentations
by a Creative Interactive Gesture Camera, so that a pointer can be moved on
the screen while the presenter moves his hand in front of the camera.
   Any presentation software can be used as long as slides are changed using
left/right arrow keys. Optionally animations can be activated with the
mouse left click.
   The presenter changes the slides using left/right swipes and a single tap
can be used to either activate presentation animations or can be assigned
as left swipe. If needed, the pointer can be completely hidden.
In order to send the key or mouse events to the presentation application, make 
sure that the presentation application has the focus during presentations.
   The pointer icon (*.jpg and *.png image formats are supported) and 
its size are configurable, also the coordinates of the
upper-left corner of the area covered by the pointer. A scaling factor can
be used in order to make sure that the entire screen area is covered by the
pointer. The number of swipes needed to activate a page switch can be changed,
the default value is one, a value of zero disables the swipe gesture, while
a value superior to one can be used if the slide switch happens too often
during presentation. By default pointer coordinates are filtered with a 
Kalman filter that can be disabled if needed.
   The following shortcut keys are available:
- F1: shows the help
- F2: shows the configuration dialog
- F3: minimizes the pointer
- Ctrl+q: quits the application
In order to receive the shortcut keys the application needs to have 
the focus (see above). In order to have the focus either click on 
the application icon on the main toolbar or click the pointer.


Installation and Utilisation

For installation use the provided installer. Application executable and required libraries are installed
in the chosen location. Also, the drivers needed by Creative Interactive Perceptual Camera are installed 
and Intel Perceptual Computing (PC) SDK 2013. An uninstaller is also provided for the application, the 
camera drivers and PC SDK need to be uninstalled separately.
The application has been tested on Windows 7, 32 bits and Windows 8. Please be aware that this application
has soft-real time requirements, so do not use this application on a heavily loaded computer, that might slow
down the rate at which image frames are received from the camera.
