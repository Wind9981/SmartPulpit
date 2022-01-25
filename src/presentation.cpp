#include "presentation.h"
#include <string>

void Presentation::Present(const QString &paramater){
	QString str1 = "/home/hoang/workspace/faceregconition/mtcnn_facenet_cpp_tensorRT/src/present.sh " + paramater;
  	QByteArray ba = str1.toLocal8Bit();
  	const char *cmd = ba.data();
	qDebug() << cmd;
	system(cmd);	
}
