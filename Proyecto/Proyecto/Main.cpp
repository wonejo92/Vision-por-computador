#include "Header.h"

int main(int argc, char* argv[]) {


	Proyecto* p = new Proyecto();
	p->Prosesamiento();
	p->ColorDetection();

	waitKey(0);
	destroyAllWindows();
	return 0;
};