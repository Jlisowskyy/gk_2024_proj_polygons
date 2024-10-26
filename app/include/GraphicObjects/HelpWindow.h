//
// Created by Jlisowskyy on 26/10/24.
//

#ifndef APP_HELPWINDOW_H
#define APP_HELPWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>


class HelpWindow : public QDialog {
Q_OBJECT

public:
    explicit HelpWindow(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Help");
        setModal(true);
        setMinimumSize(600, 800);

        QVBoxLayout *layout = new QVBoxLayout(this);

        QTextEdit *textEdit = new QTextEdit(this);
        textEdit->setReadOnly(true);
        textEdit->setHtml(R"(
            <h2>Instrukcja użytkowania</h2>

            <h3>1. Panel przycisków</h3>

            <h4>A) Segment 'Space':</h4>
            <ul>
                <li><b>Kosz</b> - usuwa wszystkie obiekty z przestrzeni</li>
                <li><b>Kursor</b> - toggle button pozwalający włączyć dodawanie wierzchołków</li>
                <li><b>Strzałki</b> - toggle button pozwalający włączyć przesuwanie obiektów</li>
                <li><b>Debug</b> - pozwala na przesunięcie konkretnego wierzchołka o konkretną wartość</li>
            </ul>

            <p><i>Ważne uwagi:</i></p>
            <ul>
                <li>Dodawać ograniczenia można tylko z wyłączonymi przyciskami 'kursor' i 'strzałki'</li>
                <li>'Strzałki' mają priorytet nad 'kursor'</li>
            </ul>

            <h4>B) Segment 'Edge':</h4>
            <p><i>Uwaga: Niektóre przyciski są dostępne dopiero po zaznaczeniu krawędzi</i></p>
            <ul>
                <li><b>Pędzel</b> - zmienia algorytm rysowania krawędzi</li>
                <li><b>Tasak</b> - dodaje nowy wierzchołek na środku krawędzi</li>
                <li><b>Pozioma prosta</b> - nakłada poziome ograniczenie na krawędź</li>
                <li><b>Pionowa prosta</b> - nakłada pionowe ograniczenie na krawędź</li>
                <li><b>Linijka</b> - nakłada ograniczenie stałej długości na krawędź</li>
                <li><b>Litera B</b> - zamienia krawędź w krzywą</li>
            </ul>

            <h4>C) Segment 'Vertex':</h4>
            <p><i>Uwaga: Niektóre przyciski są dostępne dopiero po zaznaczeniu wierzchołka</i></p>
            <ul>
                <li><b>G0</b> - obecnie nieaktywne</li>
                <li><b>G1</b> - nakłada ograniczenie G1 na wierzchołek</li>
                <li><b>C1</b> - nakłada ograniczenie C1 na wierzchołek</li>
            </ul>

            <h3>2. Opis algorytmu ograniczeń</h3>
            <p><i>Uwaga: Bezier jest ograniczeniem, tym samym co pozostałe, co ułatwia zarządzanie</i></p>

            <h4>A) Przesuwanie normalnego wierzchołka:</h4>
            <ol>
                <li>Propaguj zmiany do lewej na 'dry mode'</li>
                <li>Jeśli się nie powiodło, przesuń całość</li>
                <li>Propaguj zmiany do prawej na 'dry mode'</li>
                <li>Jeśli się nie powiodło, przesuń całość</li>
                <li>Powtórz sekwencję bez 'dry mode'</li>
                <li>Wyrównaj punkty kontrolne bezierów</li>
            </ol>

            <h4>B) Przesuwanie punktu kontrolnego:</h4>
            <p><i>Uwaga: Obliczenia wymagają dopracowania</i></p>
            <ol>
                <li>Oblicz jak przesunąć wierzchołek</li>
                <li>Propaguj zmiany w odpowiednim kierunku na 'dry mode'</li>
                <li>Jeśli się nie powiedzie, przesuń całość</li>
                <li>Powtórz bez 'dry mode'</li>
            </ol>
        )");

        QPushButton *closeButton = new QPushButton("Close", this);
        connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

        layout->addWidget(textEdit);
        layout->addWidget(closeButton);

        textEdit->setStyleSheet(R"(
            QTextEdit {
                font-size: 12pt;
                line-height: 1.4;
                padding: 10px;
            }
        )");
    }
};

#endif //APP_HELPWINDOW_H
