#include "menu_of_song.h"

menu_of_song::menu_of_song() {
    this->setFixedSize(25,25);
}

void menu_of_song::getstyle(bool flag)
{
    QString back_color = "";
    if(flag){
        back_color = "white";
    }else{
        back_color = "silver";
    }
    if(menu_type == 1){
        this->setStyleSheet("QPushButton {"
                           "background-color: "+back_color+";"
                           "border-image:url(:icon/play.png) 10 10 10 10 stretch stretch;"
                            "}"
                            "QPushButton:hover {"
                            "background-color: "+back_color+"; "
                            "border-image:url(:icon/play.png) 12 12 12 12 stretch stretch;"
                            "}"
                            "QPushButton:pressed {"
                            "background-color: "+back_color+"; "
                            "border-image:url(:icon/play.png) 0 0 0 0 scale-down;"
                            "}");
    }else if(menu_type == 2){
        this->setStyleSheet("QPushButton {"
                           "background-color: "+back_color+";"
                           "border-image:url(:icon/addd.png) 10 10 10 10 stretch stretch;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: "+back_color+"; "
                           "border-image:url(:icon/addd.png) 12 12 12 12 stretch stretch;"
                           "}"
                           "QPushButton:pressed {"
                           "background-color: "+back_color+"; "
                           "border-image:url(:icon/addd.png) 0 0 0 0 scale-down;"
                           "}");
    }else if(menu_type == 3){
        this->setStyleSheet("QPushButton {"
                           "background-color: "+back_color+";"
                           "border-image:url(:icon/dele.png) 10 10 10 10 stretch stretch;"
                           "}"
                           "QPushButton:hover {"
                           "background-color: "+back_color+"; "
                           "border-image:url(:icon/dele.png) 12 12 12 12 stretch stretch;"
                           "}"
                           "QPushButton:pressed {"
                           "background-color: "+back_color+"; "
                           "border-image:url(:icon/dele.png) 0 0 0 0 scale-down;"
                           "}");
    }
}
