#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true); // 接受drop事件
    ui->graphicsView->setAcceptDrops(false); // 禁用graphicsView的acceptDrops，因为我们希望能够抓住放在窗口上任何一个地方的图
    ui->graphicsView->setScene(&scene);

    ui->graphicsView->setInteractive(true);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setRubberBandSelectionMode(Qt::ContainsItemShape);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 接受drop事件
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList acceptedFileTypes; // 接受的文件类型
    acceptedFileTypes.append("jpg");
    acceptedFileTypes.append("png");
    acceptedFileTypes.append("bmp");

    if (event->mimeData()->hasUrls() &&
            event->mimeData()->urls().count() == 1)
    {

        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if(acceptedFileTypes.contains(file.suffix().toLower()))
        {
            event->acceptProposedAction(); // 接受drop事件
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QPoint viewPos = ui->graphicsView->mapFromParent(event->pos()); // 从window -> view里面
    QPointF sceneDropPos = ui->graphicsView->mapToScene(viewPos); // view -> scene

    QFileInfo file(event
                   ->mimeData()
                   ->urls()
                   .at(0)
                   .toLocalFile());
    QPixmap pixmap;
    if(pixmap.load(file.absoluteFilePath()))
    {
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        // item->setGraphicsEffect(new QCustomGraphicsEffect); // 设置item的效果
        item->setPos(sceneDropPos);
        item->setFlag(QGraphicsItem::ItemIsSelectable);
        item->setAcceptedMouseButtons(Qt::LeftButton);
        scene.addItem(item); // 也可以使用QgraphicsScene的addPixmap函数。scene.addPixelMap(pixmap);
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("The image file cannot be read!"));
    }
    // addWidget函数可以用来向场景中添加Qt控件。除了某些特殊的控件（即带Qt::WA_PaintOnScreen标记集的控件，或用外部库如OpenGL或Active-X绘制的控件），可以向场景中添加任意一个其他控件
}
