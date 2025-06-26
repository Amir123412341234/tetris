#include <iostream>
#include <vector>
using namespace std;
struct Position {
    int hor_pos, ver_pos;
    Position(int hor, int ver) {
        hor_pos = hor;
        ver_pos = ver;
    }
};
struct Figure {
    vector<Position> items;
    bool move_left(int gf_h, int gf_w) {
        for (int i = 0; i < items.size(); ++i) {
            items[i].hor_pos--;
        }
        bool iscorrect = true;
        for (int i = 0; i < items.size(); ++i) {
            if(items[i].hor_pos < 0){
                iscorrect = false;
            }
        }
        if(iscorrect == false){
            move_right(gf_h, gf_w);
        }
        return iscorrect;
    }
    bool move_right(int gf_h, int gf_w) {
        for (int i = 0; i < items.size(); ++i) {
            items[i].hor_pos++;
        }
        bool iscorrect = true;
        for (int i = 0; i < items.size(); ++i) {
            if(items[i].hor_pos >= gf_w){
                iscorrect = false;
            }
        }
        if(iscorrect == false){
            move_left(gf_h, gf_w);
        }
        return iscorrect;
    }
    bool move_down(int gf_h, int gf_w) {
        for (int i = 0; i < items.size(); ++i) {
            if(items[i].ver_pos >= gf_h - 1){
                return false;
            }
        }
        for (int i = 0; i < items.size(); ++i) {
            items[i].ver_pos++;
        }
        return true;
    }
};
class GameField {
    vector<vector<int>> gamefield;
    Figure figure;
    int gf_h, gf_w;
public:
    GameField(int h, int w) {
        gamefield.resize(h);
        for (int i = 0; i < h; ++i) {
            gamefield[i].resize(w);
            for (int j = 0; j < w; ++j) {
                gamefield[i][j] = ' ';
            }
        }
        gf_h = h;
        gf_w = w;
        figure = random_figure();
    }
    void print() {
        vector<vector<int>> gamefield_copy = gamefield;
        for (int i = 0; i < figure.items.size(); ++i) {
            Position pos = figure.items[i];
            gamefield_copy[pos.ver_pos][pos.hor_pos] = '#';
        }
        for (int j = 0; j < gf_w; ++j) {
            cout << "-";
        }
        cout << endl;
        for (int i = 0; i < gf_h; ++i) {
            cout << "|";
            for (int j = 0; j < gf_w; ++j) {
                cout << (char)gamefield_copy[i][j];
            }
            cout << "|" << endl;
        }
        for (int j = 0; j < gf_w; ++j) {
            cout << "-";
        }
        cout << endl;
    }
    Figure create_LFigure() {
        Figure figure;
        figure.items.push_back(Position(5, 5));
        figure.items.push_back(Position(5, 6));
        figure.items.push_back(Position(5, 7));
        figure.items.push_back(Position(6, 7));
        return figure;
    }
    Figure create_IFigure() {
        Figure figure;
        figure.items.push_back(Position(7, 1));
        figure.items.push_back(Position(7, 2));
        figure.items.push_back(Position(7, 3));
        figure.items.push_back(Position(7, 4));
        return figure;
    }
    Figure create_OFigure() {
        Figure figure;
        figure.items.push_back(Position(7, 1));
        figure.items.push_back(Position(7, 2));
        figure.items.push_back(Position(8, 1));
        figure.items.push_back(Position(8, 2));
        return figure;
    }
    Figure create_TFigure() {
        Figure figure;
        figure.items.push_back(Position(7, 1));
        figure.items.push_back(Position(8, 2));
        figure.items.push_back(Position(9, 1));
        figure.items.push_back(Position(8, 1));
        return figure;
    }
    Figure random_figure() {
        int figure_type = rand() % 4;
        if (figure_type == 0) {
            return create_LFigure();
        }
        if (figure_type == 1) {
            return create_TFigure();
        }
        if (figure_type == 2) {
            return create_IFigure();
        }
        return create_OFigure();
    }
    void step() {
        char dir;
        cout << "enter direction: (a/d)";
        cin >> dir;
        if (dir == 'a') {
            figure.move_left(gf_h, gf_w);
        } else if (dir == 'd') {
            figure.move_right(gf_h, gf_w);
        }
        figure.move_down(gf_h, gf_w);
        if(figure.move_down(gf_h, gf_w) == false){
            for (int i = 0; i < figure.items.size(); i++){
                Position item = figure.items[i];
                gamefield[item.ver_pos][item.hor_pos] = '@';
            }
            figure = random_figure();
        }
        system("cls");
        print();
        // system("timeout 1 > NUL");
    }
};
int main() {
    srand(time(0));
    GameField gf(20, 15);
    gf.print();
    while (true) {
        gf.step();
    }
}
