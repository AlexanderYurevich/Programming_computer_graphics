
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

class ImageProcessor : public QMainWindow {
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
private slots:
    void openImage();
    void processImage();
private:
    void displayImage(const Mat &image, QLabel *widget);
    Mat originalImage;
    QComboBox *elementShapeComboBox;
    QComboBox *operationComboBox;
    QSpinBox *elementSizeSpinBox;
    QLabel *sharpenedImageWidget;
    QLabel *originalImageWidget;
    QLabel *processedImageWidget;
};
