#ifndef GUI
#define GUI
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QDebug>
#include "clickablegraphicsview.h"

class gui : public QObject
{
    Q_OBJECT
private:
    int width, height, rows, columns, size;
    QGraphicsScene* scene;
    ClickableGraphicsView* view;
    QPen penWhite, penBlack;
    QBrush brushWhite;
private slots:
    void onViewClick(QMouseEvent* event) {
        emit columnClicked(event->x() / size);
    }
signals:
    void columnClicked(int column);
public:
    gui(ClickableGraphicsView *gv, int _r, int _c)  {
        rows = _r;
        columns = _c;
        size = std::min(gv->width() / columns, gv->height() / rows);
        width = (size * columns) + 1;
        height = (size * rows) + 1;

        penWhite = QPen(QColor(Qt::white));
        brushWhite = QBrush(QColor(Qt::white));
        penBlack = QPen();

        scene = new QGraphicsScene(0, 0, width, height);
        scene->addRect(0, 0, width, height, penWhite, brushWhite);

        view = gv;
        int margin = (view->parentWidget()->parentWidget()->width() - getWidth()) / 2;
        view->resize(getWidth(), getHeight());
        view->move(margin, margin);
        view->setScene(scene);
        connect(view, SIGNAL(clicked(QMouseEvent*)), this, SLOT(onViewClick(QMouseEvent*)));
    }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void drawBlock(int x, int y, QBrush brush) {
        float _size = size * 0.8f;
        float margin =  (size - _size) / 2;
        int row = rows - y - 1;
        int column = x;
        scene->addEllipse((column * size) + margin, (row * size) + margin, _size, _size, penBlack, brush);
    }

    void drawGrid() {
        for (int x = 0; x < columns; ++x) {
            for (int y = 0; y < rows; ++y) {
                drawBlock(x, y, brushWhite);
            }
        }
    }

};

#endif // GUI

