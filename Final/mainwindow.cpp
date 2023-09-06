#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clases.h"

#include <QFileDialog>
#include <QDir>

double global_vis=10;
double global_doug=3;
int entrene=0;
int carge=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString filter = "Imagenes (*.pgm)";
    QString file = QFileDialog::getOpenFileName(this,"Open",QDir::homePath(),filter);
    if(file!=NULL){
        carge=carge+1;
        Filename=file;

    }

}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    global_vis=arg1;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    global_doug=arg1;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(carge>0){
        entrene=entrene+1;
        Imagen venita(Filename.toStdString());

        Skeleto calavera(venita);
        calavera.skeletizacion();
        calavera.Bifurcaciones();
        //calavera.WriteMatrix("nueva_S.pgm");

        segmentos seg(calavera);

        Douglas aproximacion(seg,global_doug);
        aproximacion.curva();


        Visvalingam Triangulos(seg,global_vis);
        Triangulos.curva();


        Unir doug(aproximacion);
        doug.lineal();
        double errorD=doug.Hausdorf(seg);
        QString errD;
        errD.sprintf("%lf",errorD);
        ui->label_6->setText(errD);

        ui->textBrowser_2->setText(doug.splines);


        //doug.WriteMatrix("nueva_D.pgm");
        doug.juntar(calavera);
        //doug.WriteMatrix("nueva_SD.pgm");

        Unir Vis(Triangulos);
        Vis.lineal();
        double errorV=Vis.Hausdorf(seg);
        QString errV;
        errV.sprintf("%lf",errorV);
        ui->label_5->setText(errV);

        ui->textBrowser->setText(Vis.splines);

        //Vis.WriteMatrix("nueva_V.pgm");
        Vis.juntar(calavera);
        //doug.WriteMatrix("nueva_SV.pgm");

        QImage image = QImage(doug.matrix.size() ,doug.matrix[0].size(), QImage::Format_RGB32);
        QGraphicsScene *graphic = new QGraphicsScene ( this );

        for(unsigned int i=0;i<	doug.matrix.size() ;i++){
            for(unsigned int j=0; j<doug.matrix[i].size();j++){
                if(doug.matrix[i][j]==0 ){
                    image.setPixel(j,i,qRgb(0,0,0));
                }
                else if (doug.matrix[i][j]==1 || doug.matrix[i][j]==-2 || doug.matrix[i][j]==-1 ){
                    image.setPixel(j,i,qRgb(112,128,144));

                }

                else if (doug.matrix[i][j]==2 ){
                    image.setPixel(j,i,qRgb(255,0,0));
                }
                else if (doug.matrix[i][j]==3){
                    image.setPixel(j,i,qRgb(255,0,0));
                }
                else if (doug.matrix[i][j]==4){
                    image.setPixel(j,i,qRgb(248,248,255));

                }
            }
        }

        graphic->addPixmap(QPixmap::fromImage(image));
        ui->graphicsView->setScene(graphic);

        QImage image2 = QImage(Vis.matrix.size() ,Vis.matrix[0].size(), QImage::Format_RGB32);
        QGraphicsScene *graphic2 = new QGraphicsScene ( this );

        for(unsigned int i=0;i<	Vis.matrix.size() ;i++){
            for(unsigned int j=0; j<Vis.matrix[i].size();j++){
                if(Vis.matrix[i][j]==0 ){
                    image2.setPixel(j,i,qRgb(0,0,0));
                }
                else if (Vis.matrix[i][j]==1 || Vis.matrix[i][j]==-2 || Vis.matrix[i][j]==-1 ){
                    image2.setPixel(j,i,qRgb(112,128,144));

                }

                else if (Vis.matrix[i][j]==2 ){
                    image2.setPixel(j,i,qRgb(255,0,0));
                }
                else if (Vis.matrix[i][j]==3){
                    image2.setPixel(j,i,qRgb(255,0,0));
                }
                else if (Vis.matrix[i][j]==4){
                    image2.setPixel(j,i,qRgb(248,248,255));

                }
            }
        }

        graphic2->addPixmap(QPixmap::fromImage(image2));
        ui->graphicsView_2->setScene(graphic2);




    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(entrene>0){
        QString file = QFileDialog::getSaveFileName(this,"Open",QDir::homePath());
        cout<< file.toStdString();
        QString file2= file + "_Douglas.png";
        QString file3= file + "_Visvalingam.png";

        const QPixmap pixmap = ui->graphicsView->grab();
        pixmap.save(file2);
        const QPixmap pixmap2 = ui->graphicsView_2->grab();
        pixmap2.save(file3);
    }

}
