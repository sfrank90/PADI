#ifndef CONFIG_H
#define CONFIG_H

/*! \file Config.h
\brief Structure file.
It contains the general stored settings which are loaded at the beginning.
*/

// Image buffer size
/*!
\def DEFAULT_IMAGE_BUFFER_SIZE
    Default image buffer size for the software
*/
#define DEFAULT_IMAGE_BUFFER_SIZE           1


// IMAGE PROCESSING
// Overlays
// Params: 1: glasses, 2:nose 3:redlips
/*!
\def OVERLAY_PARAM_1
    Standard value for reset functions. This values defines the glasses as overlay
*/
#define OVERLAY_PARAM_1              0 // selected or not
/*!
\def OVERLAY_PARAM_2
    Standard value for reset functions. This values defines the red nose as overlay
*/
#define OVERLAY_PARAM_2              0
/*!
\def OVERLAY_PARAM_3
    Standard value for reset functions. This values defines the red lips as overlay
*/
#define OVERLAY_PARAM_3              0


#endif // CONFIG_H
