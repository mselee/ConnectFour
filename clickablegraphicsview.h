#ifndef CLICKABLEGRAPHICSVIEW
#define CLICKABLEGRAPHICSVIEW
#include <QGraphicsView>
#include <QWidget>

class ClickableGraphicsView : public QGraphicsView {
    Q_OBJECT
signals:
    void clicked(QMouseEvent* event);
protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE {
        emit clicked(event);
    }
public:
    ClickableGraphicsView(QWidget *parent = 0) : QGraphicsView(parent) {}
};


#endif // CLICKABLEGRAPHICSVIEW

