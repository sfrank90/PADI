// local
#include "FaceDetection.h"

FaceDetection::FaceDetection()
{
}

cv::Mat FaceDetection::detectObjects(cv::Mat &inMat, ImageProcessingSettings settings , ImageProcessingFlags drawFlags)
{
	bool eyes_show = settings.overlayParam1;
	bool nose_show = settings.overlayParam2;
	bool mouth_show = settings.overlayParam3;
	// haarcascade files
	QString face_cascade_name = "./cascade/haarcascade_frontalface_alt.xml";
	QString eyes_cascade_name = "./cascade/haarcascade_eye_tree_eyeglasses.xml";
	QString nose_cascade_name = "./cascade/haarcascade_mcs_nose.xml";
	QString mouth_cascade_name = "./cascade/haarcascade_mcs_mouth.xml";
	cv::CascadeClassifier face_cascade;
	cv::CascadeClassifier eyes_cascade;
	cv::CascadeClassifier nose_cascade;
	cv::CascadeClassifier mouth_cascade;
	if( !face_cascade.load( face_cascade_name.toStdString() ) )
	{ 
		std::cout << "--(!)Error loading\n" << std::endl; 
		return inMat; 
	}
    if( !eyes_cascade.load( eyes_cascade_name.toStdString() ) )
	{ 
		std::cout << "--(!)Error loading\n" << std::endl; 
		return inMat;
	}
	if( !nose_cascade.load( nose_cascade_name.toStdString() ) )
	{ 
		std::cout << "--(!)Error loading\n" << std::endl; 
		return inMat;
	}
	if( !mouth_cascade.load( mouth_cascade_name.toStdString() ) )
	{ 
		std::cout << "--(!)Error loading\n" << std::endl; 
		return inMat;
	}

	// overlays
	QString fn_glasses = "./overlays/glasses.png";
	QString fn_nose = "./overlays/rednose.png";
	QString fn_lips = "./overlays/redlips.png";
		
	std::vector<cv::Rect> faces;
	cv::Mat frame_gray;

	cv::cvtColor( inMat, frame_gray, CV_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );

	// ----------------------------------------------------------------
	// iterating over all detected faces
	for( size_t i = 0; i < faces.size(); i++ )
	{
		int w;
		int h;
		if(drawFlags.showDetectionOn)
		{
			//draw rectangle for each face
			int x = faces[i].x;
			int y = faces[i].y;
			h = y+faces[i].height;
			w = x+faces[i].width;
			rectangle(inMat, cv::Point (x,y), cv::Point (w,h), cv::Scalar(255,0,255), 2, 8,	0);
		}

		cv::Mat faceROI = frame_gray( faces[i] );
		
		std::vector<cv::Rect> eyes;
		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) );
		if(eyes.size() == 0)
			eyes_show = false;

		std::vector<cv::Rect> nose;
		//-- In each face, detect nose
		nose_cascade.detectMultiScale( faceROI, nose, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(50, 50) );
		if(nose.size() == 0)
			nose_show = false;

		std::vector<cv::Rect> mouth;
		//-- In each face, detect mouth
		mouth_cascade.detectMultiScale( faceROI, mouth, 1.1, 8, 0 |CV_HAAR_SCALE_IMAGE, cv::Size(40, 40) );
		if(mouth.size() == 0)
			mouth_show = false;

		// ----------------------------------------------------------------
		// part detection draw eyes area
		if(eyes_show)
		{
			//draw detection
			if(drawFlags.showDetectionOn)
			{
				for( size_t j = 0; j < size_t(2); j++ )
				{

					cv::Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
					int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
					circle(inMat, center, radius, cv::Scalar( 255, 0, 0 ), 4, 8, 0 );
				}
			}
		}

		// ----------------------------------------------------------------
		// part detection draw nose area
		if(nose_show)
		{
			
			// draw detection
			if(drawFlags.showDetectionOn)
			{
				for( size_t k = 0; k < size_t(1); k++ )
				{
					cv::Point center( faces[i].x + nose[k].x + nose[k].width*0.5, faces[i].y + nose[k].y + nose[k].height*0.5 );
					ellipse(inMat, center, cv::Size( nose[k].width*0.5, nose[k].height*0.5), 0, 0, 360, cv::Scalar( 255, 255, 0 ), 4, 8, 0 );
				}
			}
		}

		// ----------------------------------------------------------------
		// part detection draw mouth area
		if(mouth_show)
		{
			//draw detection
			if(drawFlags.showDetectionOn)
			{
				for( size_t l = 0; l < size_t(1); l++ )
				{
					cv::Point center( faces[i].x + mouth[l].x + mouth[l].width*0.5, faces[i].y + mouth[l].y + mouth[l].height*0.5 );
					ellipse(inMat, center, cv::Size( mouth[l].width*0.5, mouth[l].height*0.5), 0, 0, 360, cv::Scalar( 125, 125, 125 ), 4, 8, 0 );
				}
			}
		}
		// -----------------------------------------------------------------
		// -----------------------------------------------------------------

		// Overlay functions
		// -----------------------------------------------------------------
		// part overlay eyes area
		if(eyes_show)
		{
			//show overlay
			if(drawFlags.showOverlaysOn)
			{
				std::vector<cv::Point> eyes_center;
				for( size_t p = 0; p < size_t(2); p++ )
				{
					cv::Point center( faces[i].x + eyes[p].x + eyes[p].width*0.5, faces[i].y + eyes[p].y + eyes[p].height*0.5 );
					eyes_center.push_back(center);
				}
				// calculate midpoint between both eyes
				cv::Point left_eye(eyes_center[0]);
				cv::Point right_eye(eyes_center[1]);
				cv::Point midpoint((left_eye.x + right_eye.x) / 2, (left_eye.y + right_eye.y) / 2);
				//circle(inMat, midpoint, 10, cv::Scalar( 255, 0, 0 ), 4, 8, 0 );
				cv::Mat output;

				//distance between eyes for scale
				cv::Point diff = left_eye - right_eye;
				int dist = (int)cv::sqrt(diff.x*diff.x + diff.y*diff.y) * 3;

				cvCreateOverlayGlasses(fn_glasses, inMat, output, midpoint, dist);
				inMat = output;
			}
		}

		// ----------------------------------------------------------------
		// part overlay mouth area
		if(mouth_show)
		{
			//show overlay
			if(drawFlags.showOverlaysOn)
			{
				for( size_t l = 0; l < size_t(1); l++ )
				{
					cv::Point location( faces[i].x + mouth[l].x, faces[i].y + mouth[l].y);
					cv::Mat output;

					cvCreateOverlay(fn_lips, inMat, output, location,  mouth[l].width);
					inMat = output;
				}
			}
		}
		// ----------------------------------------------------------------
		// part overlay nose area
		if(nose_show)
		{
			//show overlay
			if(drawFlags.showOverlaysOn)
			{
				for( size_t k = 0; k < size_t(1); k++ )
				{
					cv::Point location( faces[i].x + nose[k].x + nose[k].width*0.25, faces[i].y + nose[k].y + nose[k].height*0.25);
					cv::Mat output;

					cvCreateOverlay(fn_nose, inMat, output, location, nose[k].width/2);
					inMat = output;
				}
			}
		}
		// -----------------------------------------------------------------
	}
	// ----------------------------------------------------------------

    //Check cout
    //std::cout << "Object Detection done..." << std::endl;

	return inMat;
}

// create transparent overlay
void FaceDetection::cvCreateOverlay(QString fn, const cv::Mat& src, cv::Mat &output, cv::Point2i location, int scale)
{
	cv::Mat overlay = cv::imread(fn.toStdString(), -1);
	if(! overlay.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
		return;
    }
	double cropfactor = ((double) scale) / ((double)overlay.size().width) ;
	resize(overlay, overlay, cv::Size(static_cast<int>(overlay.size().width * cropfactor), static_cast<int>(overlay.size().height * cropfactor)), 0, 0, cv::INTER_CUBIC);

	src.copyTo(output);
	
	// start at the row indicated by location, or at row 0 if location.y is negative.
	for(int y = std::max(location.y , 0); y < src.rows; ++y)
	{
		int fY = y - location.y; // because of the translation

		// we are done of we have processed all rows of the foreground image.
		if(fY >= overlay.rows)
			break;

		// start at the column indicated by location, 

		// or at column 0 if location.x is negative.
		for(int x = std::max(location.x, 0); x < src.cols; ++x)
		{
			int fX = x - location.x; // because of the translation.

			// we are done with this row if the column is outside of the foreground image.
			if(fX >= overlay.cols)
			break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity = ((double)overlay.data[fY * overlay.step + fX * overlay.channels() + 3])	/ 255.;


			// and now combine the background and foreground pixel, using the opacity, 

			// but only if opacity > 0.
			for(int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					overlay.data[fY * overlay.step + fX * overlay.channels() + c];
				unsigned char backgroundPx =
					src.data[y * src.step + x * src.channels() + c];
				output.data[y*output.step + output.channels()*x + c] =
					backgroundPx * (1.-opacity) + foregroundPx * opacity;
			}
		}
	}
}

// create transparent overlay. special due to offset of the glasses
void FaceDetection::cvCreateOverlayGlasses(QString fn, const cv::Mat& src, cv::Mat &output, cv::Point2i location, int scale)
{
	cv::Mat overlay = cv::imread(fn.toStdString(), -1);
	if(! overlay.data )                              // Check for invalid input
    {
        std::cout <<  "Could not open or find the image" << std::endl ;
		return;
    }
	
    double cropfactor = ((double) scale) / ((double)overlay.size().width);
    //std::cout << cropfactor << std::endl;

    tem_cropfactor = cropfactor;
    //std::cout << "temp: " << tem_cropfactor << std::endl;
    try
    {
        resize(overlay, overlay, cv::Size(static_cast<int>(overlay.size().width * cropfactor), static_cast<int>(overlay.size().height * cropfactor)), 0, 0, cv::INTER_CUBIC);
        temp_glass_overlay = overlay;
    } catch (cv::Exception& e)
    {
        //return last state
        if(!temp_glass_overlay.empty())
            overlay = temp_glass_overlay;
    }

	cv::Point2i new_location(location.x - (overlay.size().width / 2), location.y - (overlay.size().height / 2));

	src.copyTo(output);
	
	// start at the row indicated by location, or at row 0 if location.y is negative.
	for(int y = std::max(new_location.y , 0); y < src.rows; ++y)
	{
		int fY = y - new_location.y; // because of the translation

		// we are done of we have processed all rows of the foreground image.
		if(fY >= overlay.rows)
			break;

		// start at the column indicated by location, 

		// or at column 0 if location.x is negative.
		for(int x = std::max(new_location.x, 0); x < src.cols; ++x)
		{
			int fX = x - new_location.x; // because of the translation.

			// we are done with this row if the column is outside of the foreground image.
			if(fX >= overlay.cols)
			break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity = ((double)overlay.data[fY * overlay.step + fX * overlay.channels() + 3])	/ 255.;


			// and now combine the background and foreground pixel, using the opacity, 

			// but only if opacity > 0.
			for(int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					overlay.data[fY * overlay.step + fX * overlay.channels() + c];
				unsigned char backgroundPx =
					src.data[y * src.step + x * src.channels() + c];
				output.data[y*output.step + output.channels()*x + c] =
					backgroundPx * (1.-opacity) + foregroundPx * opacity;
			}
		}
	}
}


