#include "mydiagram.h"
#include "ui_mydiagram.h"

MyDiagram::MyDiagram(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyDiagram)
{
    ui->setupUi(this);
    newScene = new QGraphicsScene();
    ui->graphicsView_Diagram->setScene(newScene);//creating new scene
}

MyDiagram::~MyDiagram()
{
    delete ui;
}

void MyDiagram::draw_diagram(QVector<Tier> tiersSavedVector)
{
    qDebug()<<"-drawing diagram...-";

    QHash<QString, QPoint> hashConnectionPoints;

    QColor tier_rect_color = Qt::red; //colors
    QColor layer_rect_color = Qt::blue;

    //Brushes (fill)
    QBrush diagram_brush;
    diagram_brush.setStyle(Qt::BrushStyle::DiagCrossPattern); //brush for colors

    QBrush diagram_dot_brush;
    diagram_dot_brush.setColor(Qt::white);
    diagram_dot_brush.setStyle(Qt::BrushStyle::SolidPattern);

    //Different pens
    QPen diagram_line_pen;
    diagram_line_pen.setWidth(2);
    diagram_line_pen.setColor(Qt::green);

    QPen diagram_label_pen;
    diagram_label_pen.setWidth(1);
    diagram_label_pen.setColor(Qt::gray);

    QPen diagram_layerConnections_pen;
    diagram_layerConnections_pen.setColor(Qt::magenta);
    diagram_layerConnections_pen.setWidth(2);

    QPen diagram_layerLabel_pen;
    diagram_layerLabel_pen.setColor(Qt::white);
    diagram_layerLabel_pen.setWidth(1);

    int max_tier_width = 0;

    const int tiers_offset = 5; // отступ
    int tier_RightTopCorner_PosX = 0; //
    int tier_RightTopCorner_PosY = 0;

    for (int i = 0; i<tiersSavedVector.size() ;i++) {//DRAW Tiers
        qDebug()<<"tier i cycle started:"<<i;
        qDebug()<<"tierLayersSize for i:"<<tiersSavedVector[i].tierLayersSize;

        diagram_brush.setStyle(Qt::BrushStyle::DiagCrossPattern);
        const int tierOffset = 30;

        int tierXposition = i+max_tier_width
                            +tierOffset
                            +(tier_RightTopCorner_PosX+tiers_offset);//TIER Position on diagram
        int tierYposition = (i*tierOffset)*2 ;
        int tierHeight = tiersSavedVector[i].tierLayersSize*50;

        for(int j = 0; j < tiersSavedVector[i].tierLayersSize; j++){//WIDTH Calc
            QString layer_data = tiersSavedVector[i].tierLayers[j].layerData;
            if (layer_data.size()*10 > max_tier_width)
                max_tier_width = layer_data.size()*12;
        }
        int tierWidth = max_tier_width + tierOffset;

        QGraphicsRectItem *tier_rectangle = new QGraphicsRectItem;
        diagram_brush.setColor(tier_rect_color);
        tier_rectangle->setBrush(diagram_brush);

        tier_rectangle->setRect(tierXposition, tierYposition,
                                tierWidth, tierHeight);

        newScene->addItem(tier_rectangle);

        QGraphicsSimpleTextItem *tierName_label = new
                                               QGraphicsSimpleTextItem(tiersSavedVector[i].tierName);
        tierName_label->setPos(tierXposition,
                               tierYposition-50);
        tierName_label->setPen(diagram_label_pen);

        newScene->addItem(tierName_label);


        for(int j = 0; j < tiersSavedVector[i].tierLayersSize; j++){//DRAW [i] tier's LAYERs
            qDebug()<<"layers j cycle started:"<<j;

            QString layer_data = tiersSavedVector[i].tierLayers[j].layerData;// Layer label

            QGraphicsRectItem *layer_rectangle = new QGraphicsRectItem;
            diagram_brush.setColor(layer_rect_color);
            diagram_brush.setStyle(Qt::BrushStyle::SolidPattern);
            layer_rectangle->setBrush(diagram_brush);

            // Layer position
            const int layer_offset = 5; //cosmetics
            const int layerHeight = 25;
            const int layerSizeWidth = 10;

            int layerXposition = tierXposition + layerSizeWidth;
            int layerYposition = tierYposition + (layer_offset*j + layer_offset) + layerHeight * j;
            int layerWidth = layer_data.size()*layerSizeWidth;
            layer_rectangle->setRect(layerXposition, layerYposition,
                                     layerWidth, layerHeight);

            newScene->addItem(layer_rectangle);

            //Drawing label
            QGraphicsSimpleTextItem *layer_inner_data = new QGraphicsSimpleTextItem(layer_data);
            layer_inner_data->setPos(layerXposition+2,
                                     layerYposition+2);
            layer_inner_data->setPen(diagram_layerLabel_pen);

            newScene->addItem(layer_inner_data);

            //Saving connection point to Hash
            hashConnectionPoints.insert(layer_data,QPoint(layerXposition,layerYposition));
        }
        //DRAW Line: connecting tiers
        //old tier's position
        int lastTier_RightTopCorner_PosX = tier_RightTopCorner_PosX;
        int lastTier_RightTopCorner_PosY = tier_RightTopCorner_PosY;

        if(i==0){// for first element
            lastTier_RightTopCorner_PosX = tierXposition;
            lastTier_RightTopCorner_PosY = tierYposition;
        };
        //current tier position:
        tier_RightTopCorner_PosX = tierXposition + tierWidth;
        tier_RightTopCorner_PosY = tierYposition;

        QGraphicsLineItem *tier_ConnectionLine = new QGraphicsLineItem;
        tier_ConnectionLine->setLine(lastTier_RightTopCorner_PosX,
                                     lastTier_RightTopCorner_PosY,
                                     tier_RightTopCorner_PosX,
                                     tier_RightTopCorner_PosY);
        tier_ConnectionLine->setPen(diagram_line_pen);
        newScene->addItem(tier_ConnectionLine);


    }
    //Drawing layers pointing lines
    for (int i = 0; i<tiersSavedVector.size() ; i++ ) {
        for (int j = 0; j < tiersSavedVector[i].tierLayersSize; j++) {
            if(tiersSavedVector[i].tierLayers[j].pointerLinked!="NULL"){
                QPoint point_A
                = hashConnectionPoints.value(tiersSavedVector[i].tierLayers[j].layerData);
                QPoint point_B
                = hashConnectionPoints.value(tiersSavedVector[i].tierLayers[j].pointerLinked);

                QGraphicsLineItem *layer_PointingLine
                        = new QGraphicsLineItem(
                            point_A.x(),
                            point_A.y(),
                            point_B.x(),
                            point_B.y());

                layer_PointingLine->setPen(diagram_layerConnections_pen);
                newScene->addItem(layer_PointingLine);

                //Cosmetics
                const int DotSize = 4;
                QGraphicsEllipseItem *cosmeticDot_A
                        = new QGraphicsEllipseItem(
                            point_A.x(),
                            point_A.y(),
                            DotSize,
                            DotSize);

                QGraphicsEllipseItem *cosmeticDot_B
                        = new QGraphicsEllipseItem(
                            point_B.x(),
                            point_B.y(),
                            DotSize,
                            DotSize);

                cosmeticDot_A->setBrush(diagram_dot_brush);
                cosmeticDot_B->setBrush(diagram_dot_brush);
                newScene->addItem(cosmeticDot_A);
                newScene->addItem(cosmeticDot_B);

            }
        }
    }

}

