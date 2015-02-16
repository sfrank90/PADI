#ifndef STRUCTURES_H
#define STRUCTURES_H

/*! \file Structures.h
\brief Structures of the program.
This file contains to structures to share settings and flags programm wide.
*/

//! Structure which contains information about the overlays apply on the image.
/*!
    Structure with three boolean values.
*/
struct ImageProcessingSettings{
    //! Bool.
    /*!
    Boolean value if glasses shall be displayed.
    */
    bool overlayParam1; // eyes
    //! Bool.
    /*!
    Boolean value if funny nose shall be displayed.
    */
    bool overlayParam2; // nose
    //! Bool.
    /*!
    Boolean value if red lips shall be displayed.
    */
    bool overlayParam3; // mouth
};

//! Structure which contains information about the flags. Determine what process shall be done.
/*!
    Structure with two boolean values.
*/
struct ImageProcessingFlags{
    //! Bool.
    /*!
    Boolean value if detection shall be drawn.
    */
    bool showDetectionOn;
    //! Bool.
    /*!
    Boolean value if overlays shall be drawn.
    */
	bool showOverlaysOn;
};

#endif // STRUCTURES_H
