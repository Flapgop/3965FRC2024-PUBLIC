#ifndef START_HERE_H
#define START_HERE_H

// This is where you'll find all the magical things that do things that you can't configure in the GUI
// Mostly hardware configuration, although I don't know what else might go here

// HARDWARE ========================================================================================================================================
// Uncomment any of the following features to enable hardware

// Uses a custom driver to make omni wheels function more compatibility (Requires at least 4 motors, 1 for each wheel)
// #define OMNI_WHEELS

// Adds object recognition support, this basically makes the autonomous period actually do something useful. (Requires Limelight)
#define LIMELIGHT
// This is extremely necessary for object recognition, because it enables the Google Coral TPU for Limelight. (Requires Limelight and Google Coral)
// #define LIMELIGHT_ML

#endif