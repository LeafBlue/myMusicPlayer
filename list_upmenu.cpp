#include "list_upmenu.h"

list_upmenu::list_upmenu() {
    this->setFixedSize(100,30);
    this->setStyleSheet("QPushButton {background-color: SlateGray;color:silver;font-size:20px;font-weight: bold;border:0.5px solid DimGray; }"
                        "QPushButton:hover {background-color: DarkSlateGray;color:silver;font-size:20px;font-weight: bold;border:0.5px solid DimGray; }"
                        "QPushButton:pressed {background-color: DarkSlateGray;color:silver;font-size:18px;font-weight: bold;border:2px solid DimGray; }");
}
