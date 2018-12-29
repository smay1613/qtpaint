#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include "command.h"
#include <QPainter>
#include <QObject>
#include <QMouseEvent>
#include <memory>
#include "../strategies/drawstrategy.h"
#include "drawcommandmemento.h"

class DrawCommand : public QObject, public ICommand
{
    Q_OBJECT
public:
    explicit DrawCommand(QPainter* painter);
    DrawCommand(QPainter* painter, std::unique_ptr<IDrawStrategy> strategy);
    virtual ~DrawCommand() = default;

    virtual void execute(const QMouseEvent& mouseState, bool paintStarted);
    virtual void execute() override;

    void setPainter(QPainter *painter);

    QPen pen() const;
    void setPen(const QPen &pen);

    DrawCommandMemento getMemento() const;
    virtual PaintTypes::ShapeType type() const = 0;

    void retrieveMemento(DrawCommandMemento memento);

signals:
    void updateRequested();

protected:
    QPainter* m_painter;
    QPen m_pen;
    std::unique_ptr<IDrawStrategy> m_drawStrategy;
};

#endif // DRAWCOMMAND_H
