#include "LexicalAnalyzer.h"
#define MAYORIGUAL 258
#define MENORIGUAL 259
#define DIFERENTEIGUAL
LexicalAnalyzer::LexicalAnalyzer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

bool LexicalAnalyzer::isLineBreak(char ch)
{
    if (ch == '\n')
    {
        return true;
    }
    return false;
}

bool LexicalAnalyzer::isPunctuator(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|' || ch == '\n' || ch==':' || ch== '!')
    {
        return true;
    }
    return false;
}

bool LexicalAnalyzer::validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isPunctuator(str[0]) == true)
    {
        return false;
    }
    int i, len = strlen(str);
    if (len == 1)
    {
        return true;
    }
    else
    {
        for (i = 1; i < len; i++)
        {
            if (isPunctuator(str[i]) == true)
            {
                return false;
            }
        }
    }
    return true;
}

bool LexicalAnalyzer::isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&' || ch=='!')
    {
        return true;
    }
    return false;
}

bool LexicalAnalyzer::isKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "endl") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "volatile") || !strcmp(str, "typedef") || !strcmp(str, "enum") || !strcmp(str, "const") || !strcmp(str, "union") || !strcmp(str, "extern") || !strcmp(str, "bool") || !strcmp(str, "main") || !strcmp(str, "cout") || !strcmp(str, "string"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalyzer::isNumber(char* str)
{
    int i, len = strlen(str), numOfDecimal = 0;
    if (len == 0)
    {
        return false;
    }
    for (i = 0; i < len; i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
        {
            return false;
        }
        else if (numOfDecimal <= 1)
        {
            numOfDecimal++;
        }
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
        {
            return false;
        }
    }
    return true;
}

char* LexicalAnalyzer::subString(char* realStr, int l, int r)
{
    int i;

    char* str = (char*)malloc(sizeof(char) * (r - l + 2));

    for (i = l; i <= r; i++)
    {
        str[i - l] = realStr[i];
        str[r - l + 1] = '\0';
    }
    return str;
}

void LexicalAnalyzer::parse(char* str)
{
    QString result;
    int left = 0, right = 0;
    int len = strlen(str);
    while (right <= len && left <= right)
    {
        if (isPunctuator(str[right]) == false)
        {
            right++;
        }

        if (isPunctuator(str[right]) == true && left == right)
        {
            if (isOperator(str[right]) == true)
            {
                if (isPunctuator(str[right+1]) && str[right+1] == '=' && str[right]=='>')
                {
                    std::string message = "TOKEN OPERADOR[";
                    message += '>';
                    message += '=';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN OPERADOR"
                        << "[" << '>' << '=' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '=' && str[right]=='<')
                {
                    std::string message = "TOKEN OPERADOR[";
                    message += '<';
                    message += '=';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN OPERADOR"
                        << "[" << '<' << '=' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '=' && str[right] == '=')
                {
                    std::string message = "TOKEN OPERADOR[";
                    message += '=';
                    message += '=';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN OPERADOR"
                        << "[" << '=' << '=' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '=' && str[right] == '!')
                {
                    std::string message = "TOKEN OPERADOR[";
                    message += '!';
                    message += '=';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN OPERADOR"
                        << "[" << '!' << '=' << "]\n";
                    right++;
                }
                else if (isOperator(str[right + 1]) && str[right + 1] == '+' && str[right] == '+')
                {
                    std::string message = "TOKEN INCREMENTO[";
                    message += '+';
                    message += '+';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN INCREMENTO"
                        << "[" << '+' << '+' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '-' && str[right] == '-')
                {
                    std::string message = "TOKEN DECREMENTO[";
                    message += '-';
                    message += '-';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN DECREMENTO"
                        << "[" << '-' << '-' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '=' && str[right] == '+')
                {
                    std::string message = "TOKEN INCREMENTO_IGUAL[";
                    message += '+';
                    message += '=';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN INCREMENTO_IGUAL"
                        << "[" << '+' << '=' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '=' && str[right] == '-')
                {
                    std::string message = "TOKEN DECREMENTO_IGUAL[";
                    message += '-';
                    message += '=';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN DECREMENTO_IGUAL"
                        << "[" << '-' << '=' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '<' && str[right] == '<')
                {
                    std::string message = "TOKEN SALIDA_STD[";
                    message += '<';
                    message += '<';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN SALIDA_STD"
                        << "[" << '<' << '<' << "]\n";
                    right++;
                }
                else if (isPunctuator(str[right + 1]) && str[right + 1] == '>' && str[right] == '>')
                {
                    std::string message = "TOKEN ENTRADA_STD[";
                    message += '>';
                    message += '>';
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    std::cout << "TOKEN ENTRADA_STD"
                        << "[" << '>' << '>' << "]\n";
                    right++;
                }
                else
                {
                    std::string message = "TOKEN OPERADOR[";
                    message += str[right];
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);

                    std::cout << "TOKEN OPERADOR"
                        << "[" << str[right]<< "]\n";
                }
            }
            else if (isPunctuator(str[right]) == true)
            {
                if (str[right] != '\n')
                {
                    std::string message = "TOKEN SP[";
                    message += str[right];
                    message += ']';
                    message += '\n';
                    result += QString::fromStdString(message);
                    ui.output->setText(result);
                    std::cout << "TOKEN SP"
                        << "[" << str[right] << "]\n";
                }
            }
            right++;
            left = right;
        }
        else if (isPunctuator(str[right]) == true && left != right || (right == len && left != right))
        {
            char* sub = subString(str, left, right - 1);
            if (isKeyword(sub) == true)
            {
                std::string message = "TOKEN PR[";
                message += sub;
                message += ']';
                message += '\n';
                result += QString::fromStdString(message);
                ui.output->setText(result);
                std::cout << "TOKEN PR"
                    << "[" << sub << "]\n";
            }
            else if (isNumber(sub) == true)
            {
                std::string message = "TOKEN NUM[";
                message += sub;
                message += ']';
                message += '\n';
                result += QString::fromStdString(message);
                ui.output->setText(result);
                std::cout << "TOKEN NUM"
                    << "[" << sub << "]\n";
            }
            else if (validIdentifier(sub) == true && isPunctuator(str[right - 1]) == false)
            {
                std::string message = "TOKEN ID[";
                message += sub;
                message += ']';
                message += '\n';
                result += QString::fromStdString(message);
                ui.output->setText(result);
                std::cout << "TOKEN ID"
                    << "[" << sub << "]\n";
            }
            else if (validIdentifier(sub) == false && isPunctuator(str[right - 1]) == false)
            {
                std::string message = "TOKEN NO-ID[";
                message += sub;
                message += ']';
                message += '\n';
                result += QString::fromStdString(message);
                ui.output->setText(result);
                std::cout << "TOKEN NO-ID"
                    << "[" << sub << "]\n";
            }

            left = right;
        }
    }
    return;
}

LexicalAnalyzer::~LexicalAnalyzer()
{}

void LexicalAnalyzer::on_analyze_clicked()
{
    if (ui.input->toPlainText().isEmpty())
    {
        ui.warning->setText("Inserte Codigo a analizar");
    }
    else
    {
        QString input = ui.input->toPlainText();
        std::string test = input.toStdString();
        char* str;
        strcpy(str, test.c_str());
        this->parse(str);
    }
}
void LexicalAnalyzer::on_clear_clicked()
{
    ui.input->clear();
    ui.output->clear();
}

void LexicalAnalyzer::on_exit_clicked()
{
    this->close();
}