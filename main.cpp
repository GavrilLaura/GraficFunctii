/*
GRAFICUL FUNCTIEI
ADAM ALESSIA-NICOLETA
GAVRIL LAURA-ELENA
ANUL I, GRUPA A3
*/

#include <iostream>
#include<iomanip>
#include<stack>
#include<stdlib.h>
#include <stdio.h>
#include<cstring>
#include<climits>
#include<limits>
#include<cmath>
#define infinit INT_MAX
#define epsi 0.0001
#include<string>
#include<graphics.h>
#include <conio.h>

using namespace std;
int offsetX = 300;  // Poziția inițială pe axa X
int offsetY = 200;  // Poziția inițială pe axa Y
bool dragging = false; // Flag pentru a verifica dacă se trage
int lastMouseX, lastMouseY; // Coordonatele anterioare ale mouse-ului
const float pi=3.1415926;
const float e=2.71828;
char OperatiiBinare[200]="+-*/^<>=#";
char OperatiiUnare[200]="scarel";
char Operatii[200]="+-*/^<>=#scarel";
char expresie[256],v[256][256];
int k=0;

bool numar(char v[])//verifica daca un caracter este numar, pi sau e
{
    return isdigit(v[0]) ||v[0]=='q' || v[0]=='e';
}

bool oper(char c)//verifica daca caracterul este operator binar
{
    return c=='+' || c=='-' || c=='*' || c=='/' ||c=='^' ||c=='#' ||c=='=' || c=='>' ||c=='<';
}
bool operunar(const char v[])//verifica daca sirul de caractere este operator unar
{
    return strcmp(v,"sin")==0 || strcmp(v,"cos")==0 || strcmp(v,"log")==0 || strcmp(v,"sqrt") == 0 || strcmp(v,"abs")==0 || strcmp(v,"exp")==0 || strcmp(v,"n")==0;
}

void tokeni(char expresie[], char v[256][256],int &k)//imparte expresia in tokeni
{
    int n=strlen(expresie),p;
    for(int i=0;i<n;i++)
    {
        if(isspace(expresie[i])) continue;//isspace- verifica daca este spatiu alb(spatiu, \n..)
        if(oper(expresie[i])==1 || expresie[i]=='(' ||expresie[i]==')')
        {
                v[k][0]=expresie[i];
                v[k][1]='\0';//asigura ca este sir valid de caractere
                k++;
        }
        else if(isalpha(expresie[i]))//sin,cos,log...sau x
        {
            p=0;
            while(i<n&& isalpha(expresie[i]))
            {
                v[k][p++]=expresie[i];
                i++;
            }
            v[k][p]='\0';
            k++;
            i--;

        }
        else if(isdigit(expresie[i]))//formeaza numarul/numerele
        {
            p=0;
            while(i<n && isdigit(expresie[i]) || expresie[i]=='.')
            {
                v[k][p++]=expresie[i];
                i++;
 }
            v[k][p]='\0';
            k++;
            i--;
        }
    }
}

bool verifica_paranteze(char expresie[])//verifica corectitudinea parantezelor
{
    stack<char> stiva;
    for (int i = 0; i < strlen(expresie); ++i)
    {
        if (expresie[i] == '(')
        {
            stiva.push(expresie[i]);
        }
        else if (expresie[i] == ')')
        {
            if (stiva.empty()) return false;
            stiva.pop();
        }
    }
    return stiva.empty();
}
bool verifica_elemente(char v[][256], int k)//verifica daca operatorii sunt amplasați corect
{
    for (int i = 0; i < k; i++)
    {
        if (v[i][0]=='n')
        {
            if(v[i+1][0]!='(' && v[i+3][0]!=')' ) return false;
        }
        if (operunar(v[i]) && strcmp(v[i], "neg")!=0)
        {
            if (i + 1 >= k || v[i + 1][0] != '(') return false;
        }
        else if (v[i][0] == '<' || v[i][0] == '>' || v[i][0] == '=' || v[i][0] == '#')
        {
            if (i - 2 < 0 || i + 2 >= k || v[i - 2][0] != '(' || v[i + 2][0] != ')') return false;
        }
        else if ((numar(v[i]) || v[i][0] == 'x'))
        {
            if (i + 1 < k && !oper(v[i + 1][0]) && v[i + 1][0] != ')') return false;
        }
        else if (v[i][0] == '(')
        {
            if (i + 1 >= k || (!numar(v[i + 1]) && v[i + 1][0] != 'x' && !operunar(v[i + 1]) && v[i + 1][0] != '+' && v[i + 1][0] != '-')) return false;
        }
        else if (v[i][0] == ')')
        {
            if (i + 1 < k && !oper(v[i + 1][0]) && v[i + 1][0] != ')') return false;
        }
        else if (oper(v[i][0]))
        {
            if (i + 1 >= k || v[i + 1][0] == ')' || oper(v[i + 1][0])) return false;
        }
        else return false;
    }
    return true;
}
bool verifica_expresie(char expresie[], char v[][256], int k)//verifica corectitudinea sintactica a expresiei
{
    return verifica_paranteze(expresie) && verifica_elemente(v, k);
}

double adunare(float x, float y)
{
    return x+y;
}

double scadere(float x,float y)
{
    return x-y;
}

double inmultire(float x, float y)
{
    return x*y;
}

double impartire(float x, float y)
{
    return x/y;
}
double mai_mare(float x, float y)
{
    return x>y;
}

bool mai_mic(float x, float y)
{
    return x<y;
}

bool egal(float x, float y)
{
    return x==y;
}

bool diferit(float x, float y)
{
    return x!=y;
}

bool difinf(float x)//verifică dacă un număr este diferit de infinit sau nu, (daca diferenta dintre x si infinit e mare atunci x=nr.finit, altfel x=infinit
{
    return fabs(infinit-fabs(x)) > infinit / 2.0;//fabs calculeaza valoarea absoluta a unui numar
}

double logaritm(float x)
{
    if ( x>epsi && difinf(x))
        return log(x);
    else
        return infinit;
}

double exponential(float x)
{
    if (difinf(x)) return exp(x);
    else return infinit;
}
double putere(float x, float y)
{
    float p;
    if (x==0) return 0;
    else
        if (y==0) return 1;
        else
            if (x==infinit || y==infinit) return infinit;
            else
                return pow(x,y);
}

double sinus(float x)
{
    if (difinf(x))  return sin(x);
    else return infinit;
}

double cosinus(float x)
{
    if (difinf(x))  return cos(x);
    else return infinit;
}

double modul(float x)
{
    if (difinf(x)) return fabs(x);
    else return infinit;
}

double radical(float x)
{
    if (difinf(x) && (x>epsi)) return sqrt(x);
    else return infinit;
}
int Prioritate(char c)// returneaza gradul de prioritate al fiecarui operator
{
    if(c=='(' || c==')')return 0;
    if(c=='+' || c=='-')return 1;
    if(c=='*' || c=='/')return 2;
    if(c=='^')return 3;
    if(c=='=' || c=='#' || c=='<' || c=='>' || c=='n')return 4;
    else return 5;
}

double valoare_expresie(char v[][256],int k, double a)//calculeaza valoarea expresiei intr-un punct dat
{
    stack<double>Opd;//stiva operanzilor declarata de tip double
    stack<string> Op;//stiva operatorilor declarata de tip string
    Op.push("(");
    for(int i=0;i<k;i++)//se parcurge fiecare token din v
    {
        if(isdigit(v[i][0]))Opd.push(atof(v[i]));//atof converteste in double
        else if(v[i][0]=='q')Opd.push(pi);
        else if(v[i][0]=='x') Opd.push(a);
        else if(v[i][0]=='e') Opd.push(e);
        else if(v[i][0]=='(')Op.push("(");
        else if(v[i][0]==')')
        {
            while(!Op.empty()&& Op.top()!="(")
            {
                string op=Op.top();Op.pop();
                double y=Opd.top();Opd.pop();
                if (op=="+" || op=="-" || op=="*" || op=="/" ||op=="^" ||op=="#" ||op=="=" || op==">" ||op=="<")
                {
                    double x=Opd.top();Opd.pop();
                    if(op=="+") Opd.push(adunare(x,y));
                    if(op=="-") Opd.push(scadere(x,y));
                    if(op=="*") Opd.push(inmultire(x,y));
                    if(op=="^") Opd.push(putere(x,y));
                    if(op=="/") Opd.push(impartire(x,y));
                    if(op=="=") Opd.push(egal(x,y));
                    if(op=="#") Opd.push(diferit(x,y));
                    if(op=="<") Opd.push(mai_mic(x,y));
                    if(op==">") Opd.push(mai_mare(x,y));
                }
                else
                {
                    if (op == "n") Opd.push(-y);
                    if (op=="sin") Opd.push(sinus(y));
                    if (op=="cos") Opd.push(cosinus(y));
                    if (op=="log") Opd.push(logaritm(y));
                    if (op=="sqrt") Opd.push(radical(y));
                    if (op=="abs") Opd.push(modul(y));
                    if (op=="exp") Opd.push(exponential(y));
                }
            }
            if(!Op.empty())Op.pop();
        }
        else
        {
            while(!Op.empty() && Prioritate(Op.top()[0])>=Prioritate(v[i][0]))
            {
                string op=Op.top();Op.pop();
                double y=Opd.top();Opd.pop();
                if (op=="+" || op=="-" || op=="*" || op=="/" ||op=="^" ||op=="#" ||op=="=" || op==">" ||op=="<")
                {
                    double x=Opd.top();Opd.pop();
                    if(op=="+") Opd.push(adunare(x,y));
                    if(op=="-") Opd.push(scadere(x,y));
                    if(op=="*") Opd.push(inmultire(x,y));
                    if(op=="^") Opd.push(putere(x,y));
                    if(op=="/") Opd.push(impartire(x,y));
                    if(op=="=") Opd.push(egal(x,y));
                    if(op=="#") Opd.push(diferit(x,y));
                    if(op=="<") Opd.push(mai_mic(x,y));
                    if(op==">") Opd.push(mai_mare(x,y));
                }
                else
                {
                    if (op == "n") Opd.push(-y);
                    if (op=="sin") Opd.push(sinus(y));
                    if (op=="cos") Opd.push(cosinus(y));
                    if (op=="log") Opd.push(logaritm(y));
                    if (op=="sqrt") Opd.push(radical(y));
                    if (op=="abs") Opd.push(modul(y));
                    if (op=="exp") Opd.push(exponential(y));
                }
            }
            Op.push(v[i]);
        }
    }
    while(!Op.empty()&& Op.top()!="(")
    {
        string op=Op.top();Op.pop();
        double y=Opd.top();Opd.pop();
        if (op=="+" || op=="-" || op=="*" || op=="/" ||op=="^" ||op=="#" ||op=="=" || op==">" ||op=="<")
        {
            double x=Opd.top();Opd.pop();
            if(op=="+") Opd.push(adunare(x,y));
            if(op=="-") Opd.push(scadere(x,y));
            if(op=="*") Opd.push(inmultire(x,y));
            if(op=="^") Opd.push(putere(x,y));
            if(op=="/") Opd.push(impartire(x,y));
            if(op=="=") Opd.push(egal(x,y));
            if(op=="#") Opd.push(diferit(x,y));
            if(op=="<") Opd.push(mai_mic(x,y));
            if(op==">") Opd.push(mai_mare(x,y));
        }
        else
        {
            if (op == "n") Opd.push(-y);
            if (op=="sin") Opd.push(sinus(y));
            if (op=="cos") Opd.push(cosinus(y));
            if (op=="log") Opd.push(logaritm(y));
            if (op=="sqrt") Opd.push(radical(y));
            if (op=="abs") Opd.push(modul(y));
            if (op=="exp") Opd.push(exponential(y));
        }
    }
    return Opd.top();
}

void desenare_grilaj(int x1, int x2, int y1, int y2, double a, double b, double ymin, double ymax)//desenează grilajul grafcului
{
    // Adaugăm grilaj orizontal și vertical
    setcolor(LIGHTBLUE);
    // Linii verticale și valori pentru axa X
    for (int i = x1; i <= x2; i += 50)
    {
        line(i, y1, i, y2);
        double valoare_x = a + (b - a) * (i - x1) / (x2 - x1);
        char text[20];
        sprintf(text, "%.2f", valoare_x);
        settextjustify(CENTER_TEXT, TOP_TEXT);
        outtextxy(i, y1 + 10, text);
    }
    // Linii orizontale și valori pentru axa Y
    for (int i = y2; i <= y1; i += 50)
    {
        line(x1, i, x2, i);
        double valoare_y = ymax - (ymax - ymin) * (i - y2) / (y1 - y2);
        char text[20];
        sprintf(text, "%.2f", valoare_y);
        settextjustify(RIGHT_TEXT, CENTER_TEXT);
        outtextxy(x1 - 5, i, text);
    }
}
void reprezentare_grafic(double a, double b, int x1, int x2, int y1, int y2) // Desenează graficul funcției
{
    cleardevice();
    int x0, y0;        // Coordonatele axelor x și y pe ecran
    int xe, ye;        // Coordonatele curente pe ecran
    int xev, yev;      // Coordonatele anterioare pe ecran
    double x, y;       // Coordonate în planul real
    double ymin, ymax; // Valorile minime și maxime ale funcției

    // Determinăm ymin și ymax
    ymin = ymax = valoare_expresie(v, k, a);
    for (int i = 0; i <= (x2 - x1); ++i)
    {
        x = a + i * (b - a) / (x2 - x1);
        y = valoare_expresie(v, k, x);
        if (y != infinit) // Ignorăm discontinuitățile
        {
            if (y > ymax) ymax = y;
            if (y < ymin) ymin = y;
        }
    }

    // Desenează grilajul
    desenare_grilaj(x1, x2, y1, y2, a, b, ymin, ymax);

    // Determinăm x0, poziția axei y pe ecran
    x0 = round((b * x1 - a * x2) / (b - a));
    if (a <= 0 && 0 <= b)
    {
        setcolor(LIGHTGREEN);
        line(x0, y2, x0, y1); // Trasează axa y
    }

    // Determinăm y0, poziția axei x pe ecran
    y0 = round((ymax * y1 - ymin * y2) / (ymax - ymin));
    if (ymin <= 0 && 0 <= ymax)
    {
        setcolor(LIGHTGREEN);
        line(x1, y0, x2, y0); // Trasează axa x
    }

    // Inițializăm coordonatele vechi
    x = a;
    y = valoare_expresie(v, k, a);
    xev = round((x2 - x1) * x / (b - a) + (b * x1 - a * x2) / (b - a));
    yev = round((y2 - y1) * y / (ymax - ymin) + (ymax * y1 - ymin * y2) / (ymax - ymin));

    // Variabile pentru extreme și discontinuități
    double minVal = y, maxVal = y;
    int minX = xev, minY = yev, maxX = xev, maxY = yev;

    bool discontinuitate = false;

    // Trasează graficul funcției și identifică punctele de extrem și discontinuități
    for (int i = 0; i <= (x2 - x1); ++i)
    {
        x = a + i * (b - a) / (x2 - x1); // Calculăm punctele curente
        xe = round((x2 - x1) * x / (b - a) + (b * x1 - a * x2) / (b - a)); // Calculăm x pe ecran
        y = valoare_expresie(v, k, x);

        if (y != infinit) // Verificăm dacă punctul este valid
        {
            ye = round((y2 - y1) * y / (ymax - ymin) + (ymax * y1 - ymin * y2) / (ymax - ymin)); // Calculăm y pe ecran

            if (discontinuitate && xe >= x1 && xe <= x2)
            {
                setcolor(YELLOW);
                line(xe, y1, xe, y2); // Trasăm asimptota verticală
                discontinuitate = false;
            }

            // Actualizăm valorile minime și maxime
            if (y < minVal)
            {
                minVal = y;
                minX = xe;
                minY = ye;
            }
            if (y > maxVal)
            {
                maxVal = y;
                maxX = xe;
                maxY = ye;
            }

            // Trasează linia între punctul anterior și punctul curent
            setcolor(RED);
            line(xev, yev, xe, ye);

            // Actualizează coordonatele vechi
            xev = xe;
            yev = ye;
        }
        else
        {
            discontinuitate = true; // Marcare discontinuitate
        }
    }

    // Afișăm punctele de extrem
    setcolor(YELLOW);
    fillellipse(minX, minY, 5, 5);
    fillellipse(maxX, maxY, 5, 5);

    char text[50];
    sprintf(text, "Min: (%.2f, %.2f)", a + (b - a) * (minX - x1) / (x2 - x1), minVal);
    outtextxy(minX + 10, minY, text);

    sprintf(text, "Max: (%.2f, %.2f)", a + (b - a) * (maxX - x1) / (x2 - x1), maxVal);
    outtextxy(maxX + 10, maxY, text);
}

void loop(double a, double b, int x1, int x2, int y1, int y2)//permite efectul de lupă asupra graficului și deplasarea laterala a acestuia
{
    float scaleFactor= 1.0;
    bool exitLoop = false;//pentru a iesi din bucla loop
    bool needsRedraw =false;//arata daca graficul trebuie sa fie redesenat
    while (!exitLoop)
    {
        if (kbhit())//returnează o valoare diferită de zero dacă a fost apăsată o tastă,dacă da, se citește caracterul apăsat. În caz contrar, returnează 0.
        {
            char key = getch();//citeste un caracter de la tastatura,fără a aștepta Enter
            switch (key)
            {
                case '+':
                    scaleFactor *= 1.1;
                    needsRedraw = true;
                    break;
                case '-':
                    scaleFactor /= 1.1;
                    needsRedraw = true;
                    break;
                case 27://tasta Esc
                    exitLoop = true;
                    break;
            }
        }

        if (ismouseclick(WM_LBUTTONDOWN))//verifică dacă a fost efectuat un click cu butonul stâng al mouse-ului
        {
            clearmouseclick(WM_LBUTTONDOWN);// Curăță click-ul
            dragging = true;
            lastMouseX = mousex();// Obține coordonata X a mouse-ului
            lastMouseY = mousey();// Obține coordonata Y a mouse-ului
        }

        if (ismouseclick(WM_MOUSEMOVE) && dragging)//verifică dacă mouse-ul s-a mișcat în timpul tragerii
        {
            clearmouseclick(WM_MOUSEMOVE);
            int deltaX = mousex() - lastMouseX;//calculeaza delasarea pe Ox
            int deltaY = mousey() - lastMouseY;//calculeaza delasarea pe Oy
            offsetX += deltaX;
            offsetY += deltaY;
            lastMouseX = mousex();//coordonata X actualizata
            lastMouseY = mousey();//coordonata Y actualizata
            needsRedraw = true;
        }

        if (ismouseclick(WM_LBUTTONUP))//verifică dacă butonul stâng al mouse-ului a fost eliberat
        {
            clearmouseclick(WM_LBUTTONUP);
            dragging = false;
        }

        if (needsRedraw)
        {
            cleardevice();
            reprezentare_grafic(a/scaleFactor, b/scaleFactor, x1+offsetX, x2+offsetX, y1+offsetY, y2+offsetY);
            needsRedraw = false;
        }
        delay(10);//produce o intarziere de 10 milisecunde
    }
}

void creare_tabel(double a, double b)//creează un tabel cu valorile functiei f in diferite puncte din intervalul [a,b]
{
    setcolor(BLACK);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    int startX = 700;          // Poziția inițială pe axa X pentru tabel
    int startY = 100;          // Poziția inițială pe axa Y pentru tabel
    int rowHeight = 30;        // Înălțimea fiecărui rând
    int columnWidth = 100;     // Lățimea fiecărei coloane
    int numRows = 10;          // Numărul de rânduri

    double pas=(b-a)/numRows; // Calculăm pasul în funcție de numărul de rânduri
    double x=a;

    // Desenează liniile orizontale
    for (int i = 0; i <= numRows + 2; ++i)
    {
        line(startX, startY + i * rowHeight, startX + 2 * columnWidth, startY + i * rowHeight);
    }

    // Desenează liniile verticale
    for (int i = 0; i <= 2; ++i)
    {
        line(startX + i * columnWidth, startY, startX + i * columnWidth, startY + (numRows + 2) * rowHeight);
    }

    outtextxy(startX+columnWidth/2, startY+rowHeight-rowHeight/3, "x");//afiseaza x pe ecran
    outtextxy(startX+columnWidth+ columnWidth/2, startY+rowHeight-rowHeight/3, "f(x)");

    // Completează valorile tabelului
    for (int i = 1; i <= numRows+1; ++i)
    {
        char text[20];

        // Formatează și afișează valorile lui x
        sprintf(text, "%.2f", x);
        outtextxy(startX+ 5*columnWidth/6,startY+(i+1)*rowHeight-rowHeight/3,text);

        // Calculează și afișează f(x)
        double result = valoare_expresie(v, k, x);
        sprintf(text, "%.2f", result);//scrie textul in variabile de tip string
        outtextxy(startX+columnWidth+ 5*columnWidth/6,startY+(i+1)*rowHeight-rowHeight/3,text);

        x += pas;
    }
}

int main()
{
    int ok=1,optiune;
    char optiune2[4];

    initwindow(1000,700,"Grafic");
    setbkcolor(LIGHTGRAY);
    cleardevice();//curata fereastra si asigura colorarea de la inceput
    while(ok!=0)
    {
        cout<<"-------------------------" << endl;
        cout<<"1 - Adaugati o expresie" << endl;
        cout<<"2 - Inchideti programul" << endl;
        cout<<"-------------------------" << endl;
        cout<<endl;
        cout<<"Introduceti optiunea: ";
        cin>>optiune;
        cin.ignore(); // Curăță bufferul după citirea opțiunii

        if (optiune==1)
        {
            k=0; memset(v, 0, sizeof(v));//seteaza zona de memorie a lui v cu 0
            cout<<"Introduceti expresia matematica: ";
            cin.getline(expresie, 256);
            tokeni(expresie,v,k);
            if (!verifica_expresie(expresie,v,k))
            {
                cout<<"Expresia nu este corecta." <<endl;
                cout<<endl;
            }
            else
            {
                double a,b;
                cout<<"Introduceti limita inferioara(a): "; cin>>a;
                cout<<"Introduceti limita superioara(b): "; cin>>b;
                int x1=50, x2=600,y1=400,y2=100;
                reprezentare_grafic(a,b,x1,x2,y1,y2);
                creare_tabel(a,b);
                cout<<"Pentru a deplasa, mari sau micsora graful selectati optiunea DA, NU in caz contrar: ";cin>>optiune2;
                if(strstr(optiune2,"da") || strstr(optiune2,"DA"))
                {
                    cout<<"Pentru a continua sa adaugati functii apasati tasta Esc.";//exitLoop devine true
                    cout<<endl;
                    x1=50, x2=600,y1=400,y2=100;
                    loop(a,b,x1,x2,y1,y2);
                }

            }
        }
        else if (optiune==2)
        {
            ok=0;
            closegraph();
            cout<<"Programul a fost inchis."<<endl;
        }
        else
        {
            cout << "Optiune invalida. Va rugam sa incercati din nou." << endl;
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
        cout<<endl;
    }
    return 0;
}
