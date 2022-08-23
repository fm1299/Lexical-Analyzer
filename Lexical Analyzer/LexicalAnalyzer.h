#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_LexicalAnalyzer.h"
#include <iostream>
#include <cstring>
#include <string.h>
class LexicalAnalyzer : public QMainWindow
{
    Q_OBJECT

public:
    LexicalAnalyzer(QWidget *parent = nullptr);
    bool isLineBreak(char ch);
    bool isPunctuator(char ch);
    bool validIdentifier(char* str);
    bool isOperator(char ch);
    bool isKeyword(char* str);
    bool isNumber(char* str);
    char* subString(char* realStr, int l, int r);
    void parse(char* str);
    ~LexicalAnalyzer();
private slots:
    void on_analyze_clicked();
    void on_clear_clicked();
    void on_exit_clicked();
private:
    Ui::LexicalAnalyzerClass ui;
};
