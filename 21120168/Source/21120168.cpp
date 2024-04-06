#include <iostream>
#include "../Header/AppController.h"

// Thử chức năng của OpenCV: đọc 1 ảnh màu/xám và trích xuất đặc trưng cạnh

int main(int argc, char** argv)
{
    AppController* app = new AppController();
    app->run(argc, argv);

    waitKey();
    return 0;
}
