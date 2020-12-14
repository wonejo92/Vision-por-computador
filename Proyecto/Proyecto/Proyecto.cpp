#include "Header.h"

int minThreshold=19;
double dK;
int k = 3;
int kImpar = 3;
int sigma=0;
int pointerosio = 13;
int pointdilation = 39;
int thersholdValue = 0;
int radio = 0;
Mat gris;
Mat nueva;
Mat  convertidoErosionYDilatacion;
Mat ElementDilatacion;
Mat elementErosion;
Mat visualizacionEro;
Mat visualizacionDila;
int sigmaImpar = 3;



void erosion(int, void*);
void dilatacion(int, void*);

void eventoTrackThreshold(int v, void* pP) {
    dK = ((double)minThreshold) / 10;
    cout << "Nuevo kernel: " << dK << endl;

}

void eventoTrackKernel(int v, void* Pp) {

    if (v % 2 != 0)
        kImpar = v;

    cout << "KImpar: " << kImpar << endl;
}

void eventoTrackThresholdSigma(int v, void* Pp) {
    cout << "Sigma" << v;

    if (v % 2 != 0)
        sigmaImpar = v;

    cout << "KImpar: " << sigmaImpar << endl;


}

void eventoTrackThresholdDilation(int v, void* Pp) {
    cout << "Dilation" << v;

}

void eventoTrackThresholdErosion(int v, void* Pp) {
    cout << "Erosion" << v;

}

void Proyecto::Prosesamiento() {
    //VideoCapture video("4.mp4");
    //VideoCapture video("3.mp4");
    //VideoCapture video("cinthia.mp4");
    //VideoCapture video(0);

    //Deteccion de rostros
    double escala = 5.0;
    CascadeClassifier faceCascade;
    faceCascade.load("C:\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

    if (video.isOpened()) {
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("nueva", WINDOW_AUTOSIZE);
        createTrackbar("Threshold", "Video", &minThreshold, 255, eventoTrackThreshold, NULL);
        createTrackbar("K", "Video", &kImpar, 33, eventoTrackKernel, NULL);
        createTrackbar("Sigma", "Video", &sigma, 200, eventoTrackThresholdSigma, NULL);
        createTrackbar("Erosion", "Video", &pointerosio, 100, erosion, NULL);
        createTrackbar("Dilation", "Video", &pointdilation, 100, dilatacion, NULL);
        Mat frame;
        Mat anterior;
        Mat resta;
        while (3 == 3) {

            //Deteccion de multiples rostros
            video >> frame;
            resize(frame, frame, Size(), 1, 1);
            if (frame.rows <= 0 || frame.cols <= 0)
                break;

            flip(frame, frame, 1);

            //Cambio de espacio de color a gary para una mejor recocion de la cara
            cvtColor(frame, gris, COLOR_BGR2GRAY);
            resize(gris, gris, Size(gris.size().width / escala, gris.size().height / escala));

            //Vector que contendra el rectangulo
            vector<Rect> faces;
            //Facedetection
            faceCascade.detectMultiScale(gris, faces, 1.1, 3, 0, Size(30, 30));

            for (Rect area : faces) {
                Scalar drawColor = Scalar(0, 0, 255);
                rectangle(frame, Point(cvRound(area.x * escala), cvRound(area.y * escala)),
                    Point(cvRound((area.x + area.width - 1) * escala), cvRound((area.y + area.height - 1) * escala)), drawColor);
            }


            // dilate(frame, Erosion, getStructuringElement(MORPH_RECT, Size(kImpar + 2, kImpar + 2)));
            Mat gris = frame.clone();
            cvtColor(gris, gris, COLOR_BGR2GRAY);


            Mat griss;
            Mat final;
            //Cany Original

            Mat actual = frame.clone();

            if (anterior.rows == 0 || anterior.cols == 0) {
                anterior = frame.clone();
            }

            resta = abs(actual - anterior);
            GaussianBlur(gris, resta, Size(sigmaImpar, sigmaImpar), 0, 0, 0);
            medianBlur(gris, resta, sigmaImpar);

            // anterior = actual.clone();
            Canny(resta, griss, 100, minThreshold, k);
            //GaussianBlur(visualizacionEro, gaussin, Size(k, k), sigma);
            dilate(griss, convertidoErosionYDilatacion, ElementDilatacion);
            erode(convertidoErosionYDilatacion, convertidoErosionYDilatacion, elementErosion);
            


            //Deteccion de movimiento.
            int pixel1;
            nueva = frame.clone();
            for (int i = 0; i < convertidoErosionYDilatacion.rows; i++) {
                for (int j = 0; j < convertidoErosionYDilatacion.cols; j++) {
                    pixel1 = (int)convertidoErosionYDilatacion.at<uchar>(i, j);
                    if (pixel1 != 0)
                        break;
                    nueva.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//imagenO.at<Vec3b>(i, j);
                }
                for (int j = convertidoErosionYDilatacion.cols - 1; j >= 0; j--) {
                    pixel1 = (int)convertidoErosionYDilatacion.at<uchar>(i, j);
                    if (pixel1 != 0)
                        break;
                    nueva.at<Vec3b>(i, j) = Vec3b(0, 0, 0);//imagenO.at<Vec3b>(i, j);
                }
            }

            // cout << resta << "Video";
            imshow("Video", frame);
            //imshow("Diff", convertidoErosionYDilatacion);
            imshow("nueva", nueva);
             //imshow("Dilatacion Dilatacion", convertidoErosionYDilatacion);
             //imshow("Erosion", convertidoErosionYDilatacion);
            //imshow("Canny", griss);

            //imshow("Erosion", Erosion);
            //imshow("Gausian", ruidoGausianBlur);
            //imshow("Resta", resta);

            if (waitKey(120) == 27) //Pedimos que espere 23 milisegundos a que el usario presione la tecla escape
                break;
        }
        destroyAllWindows();
    }
}
void erosion(int, void*) {
    elementErosion = getStructuringElement(MORPH_CROSS, Size(2 * pointerosio + 1, 2 * pointerosio + 1), Point(pointerosio, pointerosio));

    //imshow("ErosionFinal", Erosionfinal);
}
void dilatacion(int, void*) {
    ElementDilatacion = getStructuringElement(MORPH_CROSS, Size(2 * pointdilation + 1, 2 * pointdilation + 1), Point(pointdilation, pointdilation));

    //imshow("ErosionFinal", Erosionfinal);
}


//Variables globales para Deteccion de Colores

//Point x, y, w, h;
Rect2d x, y, w, h;
Mat  diffimage, back, frame_gray;
Mat mask;
Mat frame, frameHSV, maskRed1, maskRed2, maskRedvis, maskRed;
vector<vector<Point>> contours;
Mat resta;
//Mat contornos;
vector<vector<Point> > contornos;
//Mat area;
double area;
RNG rng(12345);

void Proyecto::ColorDetection() {
    VideoCapture cap(0);
    if (cap.isOpened()) {
        namedWindow("Video", WINDOW_AUTOSIZE);
        namedWindow("Bit", WINDOW_AUTOSIZE);


        while (3 == 3) {

            cap >> frame;

            //GaussianBlur(frame, frame, Point(37, 37), 0);
            cvtColor(frame, frameHSV, COLOR_BGR2HSV);
            inRange(frameHSV, Scalar(0, 100, 20), Scalar(179, 255, 255), maskRed1);
            findContours(maskRed1, contornos, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
            drawContours(frame, contornos, -1, (230, 0, 38), 3);

            GaussianBlur(frameHSV, frameHSV, Size(3, sigmaImpar), 0, 0, 0);
            //Mat area;

            if (frame.rows <= 0 || frame.cols <= 0)
                break;

            //frame = drawing.clone();

            imshow("Video", frame);
            imshow("Bit", frameHSV);
            // imshow("Mask", maskRed2);
             //imshow("Resta", resta);


            if (waitKey(20) == 27) //Pedimos que espere 23 milisegundos a que el usario presione la tecla escape
                break;
        }


        destroyAllWindows();
    }
    
}
