//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_TOOLBAR_H
#define APP_TOOLBAR_H

#include "QObject"
#include "QToolBar"

class ToolBar : public QObject {
    Q_OBJECT

// ------------------------------
// Class creation
// ------------------------------

public:
    explicit ToolBar(QObject *parent);
    ~ToolBar() override;

// ------------------------------
// Class interaction
// ------------------------------

    void setupToolBar(QToolBar *toolBar);

// ------------------------------
// Class private methods
// ------------------------------
private:

    void addToolbarLiteral(const char* strLiteral);
    void addButtonToToolbar(const char* name, const char* imgPath, const char* toolTip);

// ------------------------------
// Class fields
// ------------------------------

    QToolBar *m_toolBar;
};


#endif //APP_TOOLBAR_H
