/*ESQUELETO PARA UM JOGO DE LABIRINTO UTILIZANDO RECURSOS APRENDIDOS EM AULA
OBS: O programa tem melhorias óbvias considerando os conteúdos vistos em aula
- Por exemplo, o arquivo não é atualizado no final da execução
Enunciado da atividade feita em aula:
Faça um programa que lê um arquivo com indicações de espaço livre(0), barreira(1), personagem(2)
O jogo deve ter uma função que permite o movimento do personagem pelas posições livres sem deixar rastro
*/
#include <iostream>
#include <fstream>
#include <conio.h> //getch()
#include <windows.h> ///remover
#include <ctime>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int fov=3;
int fov2=3;

int menu(){
    int escolha;

    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"\n\n\n";
    cout<<"                                   LABIRINTO WOOW                                "<<endl;
    cout<<"\n\n\n";
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<" [1] CONTINUAR"<<endl;
    cout<<" [2] NOVO JOGO"<<endl;
    cout<<" [3] RANKING"<<endl;
    cin>>escolha;
    system("cls");

    return escolha;
}

int pausar(){
    system("cls");
    int escolha;
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"\n\n\n";
    cout<<"                                     JOGO PAUSADO                                "<<endl;
    cout<<"\n\n\n";
    cout<<"-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<" [1] VOLTAR"<<endl;
    cout<<" [2] SALVAR"<<endl;
    cin>>escolha;
    system("cls");
    return escolha;
}

struct PLAYER {

    int x,y;

    void coord (int li, int co){
        x=li;
        y=co;
    }

};

struct ARQUIVO {
    char* nome;
    int x, y;
    int** m;
    int** m2;


    void tam(int li, int co){
        x=li;
        y=co;
    }


    void carrega (){
        m = new int*[x];
        m2 = new int*[x];
        for (int i=0; i<x; i++){
            m[i]=new int[y];
            m2[i]=new int[y];
        }

        ifstream mapa;
        mapa.open(nome);
        char c;
        int mapai;
        ///coloca na matriz o mapa
        for(int i=0; i<x;i++){
            for(int j=0; j<y;j++){
                mapa>>c;
                m[i][j]=c-48;
            }
        }
    //mapa.close();
    }
};

void mostrarCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void colorir (int cor) {

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(out, cor);
}

void posicaoxy( int column, int line){
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);


}

double relogio(clock_t inicio=0){

    clock_t soma=33.33;

    posicaoxy(17, 0);
    double tempo = ( clock() + inicio + soma ) / (double) CLOCKS_PER_SEC;
    cout<<"tempo: "<<tempo;
    return tempo;
}

void mostra_mapa (ARQUIVO a,PLAYER &p,PLAYER &p2) {
    posicaoxy(0,0);
    for (int i=p.y-fov; i<p.y+fov+1; i++){
        for (int j=p.x-fov; j<p.x+fov+1; j++){
            switch(a.m[j][i]){
            case 0: cout<<" "; break; //espaço livre
            case 9: cout<<" "; break; //espaço livre fora do mapa
            case 1: cout<<char(219); break; //parede
            case 2: cout<<char(1); break; //player 1 e 2
            case 4: cout<<char(184); break; //teleporte
            case 5: cout<<char(189); break; //item de fov
            case 6: cout<<char(241); break; //item de parar
            }
        }
        cout<<"\n";
    }
            posicaoxy(0, 25);
            cout<<char(184)<<" - TELEPORTE"<<endl;
            cout<<char(189)<<" - REDUTOR DE CAMPO DE VISAO"<<endl;
            cout<<char(241)<<" - TRAVADOR"<<endl;
}

void mostra_mapa2 (ARQUIVO a,PLAYER &p,PLAYER &p2) {
    posicaoxy(0,0);
    for (int i=p2.x-fov2; i<p2.x+fov2+1; i++){
        cout<<"\t\t\t\t\t";
        for (int j=p2.y-fov2; j<p2.y+fov2+1; j++){
            switch(a.m[i][j]){
            case 0: cout<<" "; break;
            case 9: cout<<" "; break;
            case 1: cout<<char(219); break;
            case 2: cout<<char(1); break;
            case 4: cout<<char(184); break;
            case 5: cout<<char(189); break;
            case 6: cout<<char(241); break;
            }
        }
        cout<<"\n";
    }
}

void mudafov(int jogador,PLAYER &p,PLAYER p2,int &fov,int &fov2,ARQUIVO mapa){
    if(jogador==1){
        fov2 = 1;
        mapa.m[p2.x+fov][p2.y+fov]=9;
    }else if(jogador==2){
        fov = 1;
    }
}

void salvaarquivo(ARQUIVO &a){
    ofstream mapa;
    mapa.open("labsalvo.txt");
    int c;
        ///coloca na o mapa na matriz
        for(int i=0; i<a.x;i++){
            for(int j=0; j<a.y;j++){
                c=a.m[i][j];
                mapa<<c;

            }
            mapa<<endl;
        }
        mapa.close();
}

void salvaplayer(PLAYER p1, PLAYER p2){
    ofstream xp1;
    xp1.open("xp1.txt");
    int c;
    c=p1.x;
    xp1<<c;
    xp1.close();
    ofstream xp2;
    xp2.open("xp2.txt");
    c=p2.x;
    xp2<<c;
    xp2.close();
    ofstream yp1;
    yp1.open("yp1.txt");
    c=p1.y;
    yp1<<c;
    yp1.close();
    ofstream yp2;
    yp2.open("yp2.txt");
    c=p2.y;
    yp2<<c;
    yp2.close();

}

void puxaplayer(int &x1,int &x2,int &y1,int &y2){
    int c;
    int gx1,gx2,gy1,gy2;
    ifstream xp1("xp1.txt");
    while(xp1>>c){
        gx1 = c;
    }
    x1=gx1;
    xp1.close();
    ifstream xp2("xp2.txt");
    while(xp2>>c){
        gx2 = c;
    }
    x2=gx2;
    xp2.close();
    ifstream yp1("yp1.txt");
    while(yp1>>c){
        gy1 = c;
    }
    y1=gy1;
    yp1.close();
    ifstream yp2("yp2.txt");
    while(yp2>>c){
        gy2 = c;
    }
    y2=gy2;
    yp2.close();

}

void mover (PLAYER &p, ARQUIVO &mapa, PLAYER &p2,bool &movimento1,bool &movimento2,double tempo,bool &tempoativo){
    char tecla;
    if (kbhit()) { //verifica se uma tecla foi pressionada
        switch ((tecla = getch())){
        case 'a': //a w esquerda
            if(movimento1==1){
                if(mapa.m[p.x-1][p.y]==0){
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x-1][p.y]=2;
                    p.x=p.x-1;
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x-1][p.y]==4){//Teleporte
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x-1][p.y]=4;
                    p.x = 1 + (rand() % 16);
                    p.y = 1 + (rand() % 32);
                    while(mapa.m[p.x][p.y] == 1 || mapa.m[p.x][p.y] == 9 || mapa.m[p.x][p.y] == 2 || mapa.m[p.x][p.y] == 4){
                        p.x = 1 + (rand() % 16);
                        p.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x-1][p.y]==5){//Item de Fov
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x-1][p.y]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov2=1;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov2=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x-1][p.y]==6){//Item de parar
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x-1][p.y]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento2=0;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento2=1;
                            cont=0;
                        }
                    }
                }
            }
            break; // w esquerda s direita d baixo a cima
        case 'd': //d s direita
            if(movimento1==1){
                if(mapa.m[p.x+1][p.y]==0){
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x+1][p.y]=2;
                    p.x=p.x+1;
                }
                if(mapa.m[p.x+1][p.y]==4){//Teleporte
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x+1][p.y]=4;
                    p.x = 1 + (rand() % 16);
                    p.y = 1 + (rand() % 32);
                    while(mapa.m[p.x][p.y] == 1 || mapa.m[p.x][p.y] == 9 || mapa.m[p.x][p.y] == 2 || mapa.m[p.x][p.y] == 4){
                        p.x = 1 + (rand() % 16);
                        p.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x+1][p.y]==5){//Item de Fov
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x+1][p.y]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov2=1;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov2=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x+1][p.y]==6){//Item de parar
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x+1][p.y]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento2=0;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento2=1;
                            cont=0;
                        }
                    }
                }
            }
            break;
        case 'w'://w a cima
            if(movimento1==1){
                if(mapa.m[p.x][p.y-1]==0){
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y-1]=2;
                    p.y=p.y-1;
                }
                if(mapa.m[p.x][p.y-1]==4){//Teleporte
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y-1]=4;
                    p.x = 1 + (rand() % 16);
                    p.y = 1 + (rand() % 32);
                    while(mapa.m[p.x][p.y] == 1 || mapa.m[p.x][p.y] == 9 || mapa.m[p.x][p.y] == 2 || mapa.m[p.x][p.y] == 4){
                        p.x = 1 + (rand() % 16);
                        p.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x][p.y-1]==5){//Item de Fov
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y-1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov2=1;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov2=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x][p.y-1]==6){//Item de parar
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y-1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento2=0;
                       relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento2=1;
                            cont=0;
                        }
                    }
                }
            }
            break;
        case 's'://s d baixo
            if(movimento1==1){
                if(mapa.m[p.x][p.y+1]==0){
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y+1]=2;
                    p.y=p.y+1;
                }
                if(mapa.m[p.x][p.y+1]==4){//Teleporte
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y+1]=4;
                    p.x = 1 + (rand() % 16);
                    p.y = 1 + (rand() % 32);
                    while(mapa.m[p.x][p.y] == 1 || mapa.m[p.x][p.y] == 9 || mapa.m[p.x][p.y] == 2 || mapa.m[p.x][p.y] == 4){
                        p.x = 1 + (rand() % 16);
                        p.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x][p.y+1]==5){//Item de Fov
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y+1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov2=1;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov2=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p.x][p.y+1]==6){//Item de parar
                    mapa.m[p.x][p.y]=0;
                    mapa.m[p.x][p.y+1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento2=0;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento2=1;
                            cont=0;
                        }
                    }
                }
            }
            break;

        case 'H': //cima
            if(movimento2==1){
                if(mapa.m[p2.x-1][p2.y]==0){
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x-1][p2.y]=2;
                    p2.x=p2.x-1;
                }
                if(mapa.m[p2.x-1][p2.y]==4){//Teleporte
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x-1][p2.y]=4;
                    p2.x = 1 + (rand() % 16);
                    p2.y = 1 + (rand() % 32);
                    while(mapa.m[p2.x][p2.y] == 1 || mapa.m[p2.x][p2.y] == 9 || mapa.m[p2.x][p2.y] == 2 || mapa.m[p2.x][p2.y] == 4){
                        p2.x = 1 + (rand() % 16);
                        p2.y = 1 + (rand() % 32);
                    }
                }
            }
////////////////////////////////////////////////////////////////////////
            if(mapa.m[p2.x-1][p2.y]==5){//Item de Fov
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x-1][p2.y]=0;

                clock_t inicio = tempo;

                double tempoitem;
                double cincosec=5;

                bool cont = 1;
                system("cls");
                while(cont){
                    clock_t soma=33.33;
                    tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                    fov=1;
                    relogio();
                    mostra_mapa(mapa,p,p2);
                    mostra_mapa2(mapa,p,p2);
                    mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                    if(tempoitem >= tempo + cincosec){
                        fov=3;
                        cont=0;
                    }
                }
            }
////////////////////////////////////////////////////////////////////////
            if(mapa.m[p2.x-1][p2.y]==6){//Item de parar
                mapa.m[p2.x][p2.y]=0;
                mapa.m[p2.x-1][p2.y]=0;

                clock_t inicio = tempo;

                double tempoitem;
                double cincosec=5;

                bool cont = 1;
                system("cls");
                while(cont){
                    clock_t soma=33.33;
                    tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                    movimento1=0;
                    relogio();
                    mostra_mapa(mapa,p,p2);
                    mostra_mapa2(mapa,p,p2);
                    mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                    if(tempoitem >= tempo + cincosec){
                        movimento1=1;
                        cont=0;
                    }
                }
            }

            break;
        case 'P': //baixo
            if(movimento2==1){
                if(mapa.m[p2.x+1][p2.y]==0){
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x+1][p2.y]=2;
                    p2.x=p2.x+1;
                }
                if(mapa.m[p2.x+1][p2.y]==4){//Teleporte
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x+1][p2.y]=4;
                    p2.x = 1 + (rand() % 16);
                    p2.y = 1 + (rand() % 32);
                    while(mapa.m[p2.x][p2.y] == 1 || mapa.m[p2.x][p2.y] == 9 || mapa.m[p2.x][p2.y] == 2 || mapa.m[p2.x][p2.y] == 4){
                        p2.x = 1 + (rand() % 16);
                        p2.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p2.x+1][p2.y]==5){//Item de Fov
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x+1][p2.y]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov=1;
                       relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p2.x+1][p2.y]==6){//Item de parar
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x+1][p2.y]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento1=0;
                        relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento1=1;
                            cont=0;
                        }
                    }
                }
            }
            break;
        case 'K': //esquerda
            if(movimento2==1){
                if(mapa.m[p2.x][p2.y-1]==0){
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y-1]=2;
                    p2.y=p2.y-1;
                }
                if(mapa.m[p2.x][p2.y-1]==4){//Teleporte
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y-1]=4;
                    p2.x = 1 + (rand() % 16);
                    p2.y = 1 + (rand() % 32);
                    while(mapa.m[p2.x][p2.y] == 1 || mapa.m[p2.x][p2.y] == 9 || mapa.m[p2.x][p2.y] == 2 || mapa.m[p2.x][p2.y] == 4){
                        p2.x = 1 + (rand() % 16);
                        p2.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p2.x][p2.y-1]==5){//Item de Fov
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y-1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov=1;
                        cout<<relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p2.x][p2.y-1]==6){//Item de parar
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y-1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento1=0;
                        cout<<relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento1=1;
                            cont=0;
                        }
                    }
                }
            }
            break;
        case 'M': //direita
            if(movimento2==1){
                if(mapa.m[p2.x][p2.y+1]==0){
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y+1]=2;
                    p2.y=p2.y+1;
                }
                if(mapa.m[p2.x][p2.y+1]==4){//Teleporte
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y+1]=4;
                    p2.x = 1 + (rand() % 16);
                    p2.y = 1 + (rand() % 32);
                    while(mapa.m[p2.x][p2.y] == 1 || mapa.m[p2.x][p2.y] == 9 || mapa.m[p2.x][p2.y] == 2 || mapa.m[p2.x][p2.y] == 4){
                        p2.x = 1 + (rand() % 16);
                        p2.y = 1 + (rand() % 32);
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p2.x][p2.y+1]==5){//Item de Fov
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y+1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        fov=1;
                        cout<<relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            fov=3;
                            cont=0;
                        }
                    }
                }
    ////////////////////////////////////////////////////////////////////////
                if(mapa.m[p2.x][p2.y+1]==6){//Item de parar
                    mapa.m[p2.x][p2.y]=0;
                    mapa.m[p2.x][p2.y+1]=0;

                    clock_t inicio = tempo;

                    double tempoitem;
                    double cincosec=5;

                    bool cont = 1;
                    system("cls");
                    while(cont){
                        clock_t soma=33.33;
                        tempoitem = ( clock() + inicio +soma) / (double) CLOCKS_PER_SEC;
                        movimento1=0;
                        cout<<relogio();
                        mostra_mapa(mapa,p,p2);
                        mostra_mapa2(mapa,p,p2);
                        mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

                        if(tempoitem >= tempo + cincosec){
                            movimento1=1;
                            cont=0;
                        }
                    }
                }
            }
            break;
        case 27:
            tempoativo=false;
            int guard = 0;
            guard=pausar();
            if(guard==2){
                salvaarquivo(mapa);
                salvaplayer(p,p2);
                tempoativo=true;
            }else{
                tempoativo=true;
            }
            break;
        }
    }
}

int itemparado(PLAYER &p, PLAYER &p2, int tempo,ARQUIVO mapa){
    if(mapa.m[p.x][p.y]==6){
        return 1;
    }
    return 0;
}

void ranking(double tempo){
    double tempo1,tempo2=0,tempo3=0;
    double temp1,temp2;
    double c;

    ifstream ranking1("ranking1.txt");
        while(ranking1>>c){
        tempo1 = c;
    }
    ranking1.close();
    ifstream ranking2("ranking2.txt");
        while(ranking2>>c){
        tempo2 = c;
    }
    ranking2.close();
    ifstream ranking3("ranking3.txt");
        while(ranking3>>c){
        tempo3 = c;
    }
    ranking3.close();

    if(tempo<tempo1 && tempo<tempo2 && tempo<tempo3){

        ofstream ranking1("ranking1.txt");
        temp1=tempo1;
        ranking1<<tempo;

        ofstream ranking2("ranking2.txt");
        ranking2<<temp1;

        ranking2.close();
        ranking1.close();

        ofstream ranking3("ranking3.txt");
        temp2=tempo2;
        ranking3<<temp2;
        ranking3.close();

    }else if(tempo<tempo2 && tempo<tempo3){

        ofstream ranking2("ranking2.txt");
        temp1=tempo2;
        ranking2<<tempo;

        ranking2.close();

        ofstream ranking3("ranking3.txt");
        ranking3<<temp1;
        ranking3.close();

    }else if(tempo<tempo3){

        ofstream ranking3("ranking3.txt");
        ranking3<<tempo;
        ranking3.close();
    }

}

void mostrarank(){

    double c;
    double rank1,rank2,rank3;
    ifstream ranking1("ranking1.txt");
    while(ranking1>>c){
            rank1=c;
    }
    ranking1.close();
    ifstream ranking2("ranking2.txt");
    while(ranking2>>c){
            rank2=c;
    }
    ranking2.close();
    ifstream ranking3("ranking3.txt");
    while(ranking3>>c){
            rank3=c;
    }
    ranking3.close();
    cout<<"1 - "<<rank1<<endl;
    cout<<"2 - "<<rank2<<endl;
    cout<<"3 - "<<rank3<<endl;

}

int main(){

    srand(time(NULL));
    mostrarCursor(false);
    int resmenu;
    resmenu=menu();      //1 = CONTINUAR, 2 =  NOVO JOGO 3, = RANKINGS
    PLAYER p;
    PLAYER p2;
    if(resmenu==2){
        p.coord(4,5);

        p2.coord(11,27);
    }else{
        int x1=0,x2=0,y1=0,y2=0;
        puxaplayer(x1,x2,y1,y2);
        p.coord(x1,y1);
        p2.coord(x2,y2);
        //p.coord(4,5);  //COMENTEI AS 3 LINHAS DE CIMA SO PARA TESTAR

        //p2.coord(11,27);
    }
    ///*
    ARQUIVO mapa2;
    mapa2.nome="labsalvo.txt";
    mapa2.tam(16,32);
    mapa2.carrega();

    ARQUIVO mapa;
    mapa.nome="labirinto.txt";
    mapa.tam(16,32);
    mapa.carrega();

    bool tempoativo=true;
    double tempo;
    int jogo=1;
    bool movimento1=1;
    bool movimento2=1;
    if(resmenu==2){

        clock_t inicio;

        inicio = clock(); // tempo inicial salvar variavel de inicio


        while (jogo==1){

            mostra_mapa(mapa,p,p2);
            mostra_mapa2(mapa,p,p2);

            if(tempoativo==true){
                tempo=relogio(0); //AQUI SETA O TEMPO INICIAL
            }

            if(itemparado(p,p2,tempo,mapa)==1){
                movimento2==0;
            }
            mover(p, mapa, p2,movimento1,movimento2,tempo,tempoativo);

            //condição para ganhar o jogo
            if((abs(p.x - p2.x) < fov ) and (abs(p.y-p2.y) < fov )){
                jogo = 2;

            }
            if(tempo>=60){
                jogo = 3;
            }
        }
    }
    if(resmenu==1){

        clock_t inicio;

        inicio = clock(); // tempo inicial salvar variavel de inicio


        while (jogo==1){

            mostra_mapa(mapa2,p,p2);
            mostra_mapa2(mapa2,p,p2);
            if(tempoativo==true){
                tempo=relogio(0); //AQUI SETA O TEMPO INICIAL
            }

            if(itemparado(p,p2,tempo,mapa2)==1){
                movimento2==0;
            }
            mover(p, mapa2, p2,movimento1,movimento2,tempo,tempoativo);

            //condição para ganhar o jogo
            if((abs(p.x - p2.x) < fov ) and (abs(p.y-p2.y) < fov )){
                jogo = 2;

            }
            if(tempo>=60){
                jogo = 3;
            }
        }
    }
    if(resmenu==3){

        mostrarank();

    }
    switch(jogo){
    case 2:
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n                                         P1 WINS!"<<endl;
        cout<<"\n\nO tempo de jogo foi: "<<tempo<<" Segundos.\n\n\n\n";
        ranking(tempo);
    break;
    case 3:
        system("cls");
        cout<<"\n\n\n\n\n\n\n\n                                         P2 WINS"<<endl;
        cout<<"\n\nO tempo de jogo foi: "<<tempo<<" Segundos.\n\n\n\n";
        ranking(tempo);
    break;

    }

    //*/
    return 0;
}

///CODIGO FEITO POR: ARTUR COSTA DE SOUZA, RODRIGO FAISTAUER, MATHEUS ARMANDO TIMM BARBIERI
