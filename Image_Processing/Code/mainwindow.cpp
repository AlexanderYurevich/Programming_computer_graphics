#include "mainwindow.h"


ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent) {

    QLabel *originalLabel = new QLabel("Original Image");
    QLabel *processedLabel = new QLabel("Processed Image");
    QLabel *sharpenedLabel = new QLabel("Sharpened Image");

    originalImageWidget = new QLabel;
    processedImageWidget = new QLabel;
    sharpenedImageWidget = new QLabel;

    elementShapeComboBox = new QComboBox;
    elementShapeComboBox->addItem("Rectangle");
    elementShapeComboBox->addItem("Cross");
    elementShapeComboBox->addItem("Ellipse");

    elementSizeSpinBox = new QSpinBox;
    elementSizeSpinBox->setRange(1, 20);

    operationComboBox = new QComboBox;
    operationComboBox->addItem("Dilation");
    operationComboBox->addItem("Erosion");
    operationComboBox->addItem("Opening");
    operationComboBox->addItem("Closing");

    QPushButton *openImageButton = new QPushButton("Open Image");
    QPushButton *processButton = new QPushButton("Process Image");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(originalLabel);
    layout->addWidget(originalImageWidget);
    layout->addWidget(sharpenedLabel);
    layout->addWidget(sharpenedImageWidget);
    layout->addWidget(processedLabel);
    layout->addWidget(processedImageWidget);
    layout->addWidget(new QLabel("Structuring Element:"));
    layout->addWidget(elementShapeComboBox);
    layout->addWidget(new QLabel("Element Size:"));
    layout->addWidget(elementSizeSpinBox);
    layout->addWidget(new QLabel("Operation:"));
    layout->addWidget(operationComboBox);
    layout->addWidget(openImageButton);
    layout->addWidget(processButton);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(openImageButton, SIGNAL(clicked()), this, SLOT(openImage()));
    connect(processButton, SIGNAL(clicked()), this, SLOT(processImage()));
}

void ImageProcessor::openImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");
    if (!filePath.isEmpty()) {
        originalImage = imread(filePath.toStdString(), IMREAD_GRAYSCALE);

        if (!originalImage.empty()) {
            displayImage(originalImage, originalImageWidget);
        }
    }
}

void ImageProcessor::processImage() {
    if (originalImage.empty()) {
        return;
    }

    int shape = elementShapeComboBox->currentIndex();
    int size = elementSizeSpinBox->value();
    int operation = operationComboBox->currentIndex();
    Mat kernel;
    if (shape == 0) {
        kernel = getStructuringElement(MORPH_RECT, Size(size, size));
    } else if (shape == 1) {
        kernel = getStructuringElement(MORPH_CROSS, Size(size, size));
    } else if (shape == 2) {
        kernel = getStructuringElement(MORPH_ELLIPSE, Size(size, size));
    }

    Mat processedImage;
    switch (operation) {
    case 0: // Dilation
        dilate(originalImage, processedImage, kernel);
        break;
    case 1: // Erosion
        erode(originalImage, processedImage, kernel);
        break;
    case 2: // Opening
        morphologyEx(originalImage, processedImage, MORPH_OPEN, kernel);
        break;
    case 3: // Closing
        morphologyEx(originalImage, processedImage, MORPH_CLOSE, kernel);
        break;
    default:
        return;
    }
    Mat sharpenedImage;
    Laplacian(originalImage, sharpenedImage, CV_8U);
    displayImage(processedImage, processedImageWidget);
    displayImage(sharpenedImage, sharpenedImageWidget);
}

void ImageProcessor::displayImage(const Mat &image, QLabel *widget) {
    QImage img = QImage(image.data, image.cols, image.rows, image.step, QImage::Format_Grayscale8);
    widget->setPixmap(QPixmap::fromImage(img));
    widget->adjustSize();
}
