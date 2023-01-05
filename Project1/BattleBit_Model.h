#pragma once
#include<iostream>
#include"define.h"
//#include"BattleBit_Control.h"
#include<thread>
#include"BattleBit_View.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
using namespace std;
using namespace sf;

//int display_count=0;

//class BattleBit_View;

    class Soldier {
    public:
        soldier_type type;
        war_side side;
        uchar price;
        uchar attack;
        uchar defence;
        uchar crit_rate;
        uchar hp;
        uchar attack_range;
        uchar move_range;
        uchar is_moved;
        int view_range;
        int generate_footman_rate, generate_bowman_rate, generate_knight_rate;
        int total_footman_num, total_bowman_num, total_knight_num;
        int min_generate_row, min_generate_col, max_generate_row, max_generate_col;
        int min_atk_row, min_atk_col, max_atk_row, max_atk_col;
        int pos[2];//坐标
        char move_tag;
       
        Texture soldierTex;
        Sprite soldierSprite;

         //BattleBit_View** observers;//观察者数组
        //int observer_num;//观察者的个数

        int g_nearest_row, g_nearest_col, g_step, g_min_distance;



        //静态类的使用，只能创建一个对象的实例化
        Soldier();
        static Soldier& getinstance() {
            static Soldier  instance;
            return instance;
        }

        virtual void move(Soldier***& s,int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);        //士兵移动虚函数
        virtual int atk_enemy(Soldier***& s,int row, int col, Soldier* empty1,Soldier* &atk_base, Soldier*& def_base);    //士兵攻击虚函数
        int find_nearest_enemy(Soldier***& s,int row, int col, Soldier*&atk_base,Soldier*&def_base);   //寻找最近的敌人/基地坐标
         virtual void generate_soldier(Soldier***& s, int row, int col, Soldier* empty1);//基地按比例随机生成士兵

      //  void registerObserver(BattleBit_View* o);
        //void removeObserver(BattleBit_View* o);
        //void notifyObservers(Soldier* atk_base, Soldier* def_base);

    };
    /*extern Soldier* empty1;//默认类型全空
    extern Soldier* block;//有阻挡的地方进行设置//需不需要设置？
    extern Soldier* atk_base;
    extern Soldier* def_base;
    extern int g_nearest_row, g_nearest_col, g_step, g_min_distance;
    */

     //Soldier *empty1;
    //Soldier *block;
    //Soldier* atk_base;
   // Soldier* def_base;
    //Soldier*** s;
 


    



    class Base : public Soldier {
    public://基地可以生成的士兵范围

        Base() {}
        Base(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual void move(Soldier***& s,int row, int col) ;    //空函数什么也不做    //将base的move()固定住，让base不移动
        // virtual void generate_soldier(Soldier***& s,int row,int col);
             //在一定范围内（1-10）随机生成我方士兵
        virtual int atk_enemy(Soldier***& s,int row, int col, Soldier* empty1,Soldier*& atk_base, Soldier*& def_base);//基地有自己的攻击模式
        virtual void generate_soldier(Soldier***& s, int row, int col, Soldier* empty1);
      
    };
    void Base::move(Soldier***& s, int row, int col) {}

    class Footman : public Soldier //步兵
    {
    public:
        Footman() {}
        Footman(soldier_type c_type, war_side c_side, int c_pos[]);

    };

    class Super_soldier : public Soldier //超级士兵
    {
    public:
        Super_soldier() {}
        Super_soldier(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual int atk_enemy(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);
        virtual void move(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);

    };

    class Bowman :public Soldier {//弓箭手
    public:
        Bowman() {}
        Bowman(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual int atk_enemy(Soldier***& s,int row, int col, Soldier* empty1,Soldier*& atk_base, Soldier* &def_base);//弓箭手攻击范围广，有自己的攻击方式
    };
    class Knight : public Soldier //骑兵
    {
    public:
        Knight() {}
        Knight(soldier_type c_type, war_side c_side, int c_pos[]);
        virtual void move(Soldier***& s,int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base);//骑兵移动速度快，有自己的移动方式
    };


    

    void Soldier::move(Soldier***& s,int row, int col, Soldier* empty1,Soldier*&atk_base,Soldier*&def_base) {
        int i = 0, j = 0, k = 0;
        if (is_moved == 1) { return; }//已经移动了，无需再移动
        if (atk_enemy(s,row, col, empty1, atk_base,  def_base)) {//如果攻击了敌人，也不能动
            return;
        }
        else
        {
            find_nearest_enemy(s,row, col,atk_base,def_base);
            if (g_nearest_row < pos[0])     //如果敌人在上方
            {
                if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //如果上一格是空的，则移到上一格
                    MOVE_UP

                else if (g_nearest_col < pos[1])         //如果上一格不为空，并且最近的敌人在左边，那么说明上面是友军
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //左边空的，则移到左边
                        MOVE_LEFT
                    //else if ((pos[1] != 0) && s[pos[0]][pos[1] +1] == empty1)   //右边空的，则移到左边
                           // MOVE_RIGHT
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //若右边空着，则移到右边
                    MOVE_RIGHT
            }
            else if (g_nearest_row > pos[0])  //如果敌人在下方
            {
                if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //如果下一格是空的，则移到下一格
                {

                    MOVE_DOWN

                }
                else if (g_nearest_col < pos[1])         //如果下一格不为空，并且敌人在左边，说明下一格是友军
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //左边空的，则移到左边
                        MOVE_LEFT
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //若右边空着，则移到右边
                    MOVE_RIGHT
            }
            else if (g_nearest_row == pos[0])     //如果在同一行
            {
                if (g_nearest_col < pos[1])
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //左边空的，则移到左边
                        MOVE_LEFT
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //上边空的，则移到上边
                        MOVE_UP
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //下边空的，则移到下边
                        MOVE_DOWN
                }
                else if (g_nearest_col > pos[1])
                {
                    if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)   //右边空的，则移到右边
                        MOVE_RIGHT
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //上边空的，则移到上边
                        MOVE_UP
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //下边空的，则移到下边
                        MOVE_DOWN
                }
            }
            is_moved = 1;
        }
        atk_enemy(s,row, col, empty1, atk_base, def_base);
    }

    //根据自己的视野范围，寻找最近的敌人
    int Soldier::find_nearest_enemy(Soldier***& s,int row, int col,Soldier*&atk_base, Soldier* &def_base)
    {
        int i = 0, j = 0, min_distance = 60, min_distance_row = 30, min_distance_col = 30;
        int nearest_i = 0, nearest_j = 0;//距离不能走斜线，只能横着和竖着走
        int is_atk_find_def_soldier = 0;
        int is_def_find_atk_soldier = 0;
        if (s[pos[0]][pos[1]]->side == atk)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->view_range) < 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->view_range) >=row)
            {
                imax = row-1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->view_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->view_range) >= col)
            {
                jmax = col - 1;
            }
            
            for (i = imin; i <=imax; ++i)
            {
             
                for (j = jmin; j <=jmax; ++j)
                {
                    
                    if (s[i][j]->side == def && (abs(i - pos[0]) + abs(j - pos[1])) < min_distance)
                    {
                        is_atk_find_def_soldier = 1;
                        nearest_i = i;
                        nearest_j = j;
                        min_distance = abs(i - pos[0]) + abs(j - pos[1]);
                    }

                }
            }
            if (is_atk_find_def_soldier == 0) {
                nearest_i = def_base->pos[0];
                nearest_j = def_base->pos[1];
                min_distance = abs(i - def_base->pos[0]) + abs(j - def_base->pos[1]);
            }
        }
        else if (s[pos[0]][pos[1]]->side == def)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->view_range )< 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->view_range )>= row)
            {
                imax = col - 1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->view_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->view_range) >= col)
            {
                jmax = col - 1;
            }
            for (i = imin; i <=imax; ++i)
            {
                for (j = jmin; j <=jmax; ++j)
                {
                    if (s[i][j]->side == atk && (abs(i - pos[0]) + abs(j - pos[1])) < min_distance)
                    {
                        is_def_find_atk_soldier = 1;
                        nearest_i = i;
                        nearest_j = j;
                        min_distance = abs(i - pos[0]) + abs(j - pos[1]);
                    }


                }
            }
            if (is_def_find_atk_soldier == 0) {
                nearest_i = atk_base->pos[0];
                nearest_j = atk_base->pos[1];
                min_distance = abs(i - atk_base->pos[0]) + abs(j - atk_base->pos[1]);
            }
        }
        g_nearest_row = nearest_i;        //将最近敌人的坐标传给变量
        g_nearest_col = nearest_j;
        g_min_distance = min_distance;
        return 0;
    }
    //是否暴击 
    uchar whether_crit(uchar rate)
    {
        srand(time(NULL));
        if ((rand() % 100 + 1) <= rate)
            return CRIT_DAMAGE;
        else
            return 1;
    }
    //计算伤害，包括暴击、兵种相克
    uchar damage_calculate(Soldier* be_atk, Soldier* atk)
    {
        uchar damage = 0;
        if ((be_atk->type == bowman && atk->type == knight) || (be_atk->type == footman && \
            atk->type == bowman) || (be_atk->type == knight && atk->type == footman))
        {
            damage = (atk->attack - be_atk->defence) * SPECIAL_DAMAGE * whether_crit(atk->crit_rate);
        }//相克的兵种会产生额外的伤害，并且攻击有概率会产生暴击效果
        else
            damage = (atk->attack - be_atk->defence) * whether_crit(atk->crit_rate);
        return damage;
    }

    //找出周围血量最少的士兵并攻击，攻击成功返回1，无敌人返回0
    int Soldier::atk_enemy(Soldier***& s,int row, int col, Soldier* empty1, Soldier*&atk_base, Soldier*&def_base)
    {
        uchar damage;
        uchar min_hp = 230, min_x = 30, min_y = 30, can_atk = 0;
      /*  if (s[pos[0]][pos[1]]->type == bowman) {
            find_nearest_enemy(s, row, col, atk_base, def_base);

            if (g_min_distance <= 3)
            {
                if ((damage = damage_calculate(s[g_nearest_row][g_nearest_col], s[pos[0]][pos[1]])) > s[g_nearest_row][g_nearest_col]->hp)
                {
                    s[g_nearest_row][g_nearest_col] = empty1;
                    s[g_nearest_row][g_nearest_col]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                }
                else
                {
                    s[g_nearest_row][g_nearest_col]->hp -= damage;
                }
                return 1;
            }
            else
                return 0;
        }
        else {*/

            if ((pos[0] != 0) && (s[pos[0] - 1][pos[1]]->side != side) && (s[pos[0] - 1][pos[1]]->side != mid))//如果上一格是敌人
            {
                min_hp = s[pos[0] - 1][pos[1]]->hp;
                min_x = pos[0] - 1;
                min_y = pos[1];
                can_atk = 1;
            }
            if ((pos[1] != 0) && (s[pos[0]][pos[1] - 1]->side != side) && (s[pos[0]][pos[1] - 1]->side != mid))//如果左边是敌人
            {
                can_atk = 1;
                if (s[pos[0]][pos[1] - 1]->hp < min_hp)
                {
                    min_hp = s[pos[0]][pos[1] - 1]->hp;
                    min_x = pos[0];
                    min_y = pos[1] - 1;
                }
            }
            if ((pos[1] != col - 1) && (s[pos[0]][pos[1] + 1]->side != side) && (s[pos[0]][pos[1] + 1]->side != mid))//如果左边是敌人
            {
                can_atk = 1;
                if (s[pos[0]][pos[1] + 1]->hp < min_hp)
                {
                    min_hp = s[pos[0]][pos[1] + 1]->hp;
                    min_x = pos[0];
                    min_y = pos[1] + 1;
                }
            }
            if ((pos[0] != row - 1) && (s[pos[0] + 1][pos[1]]->side != side) && (s[pos[0] + 1][pos[1]]->side != mid))//如果下一格是敌人
            {
                can_atk = 1;
                if (s[pos[0] + 1][pos[1]]->hp < min_hp)
                {
                    min_hp = s[pos[0] + 1][pos[1]]->hp;
                    min_x = pos[0] + 1;
                    min_y = pos[1];
                }
            }
            if (can_atk)         //如果有士兵在攻击范围内
            {
                if ((damage = damage_calculate(s[min_x][min_y], s[pos[0]][pos[1]])) > min_hp)
                {
                    s[min_x][min_y] = empty1;//攻击直接致死
                    s[min_x][min_y]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                }
                else
                {
                    s[min_x][min_y]->hp -= damage;//攻击不至死，减一定的血量
                    if (s[min_x][min_y]->side == def) {
                        s[min_x][min_y]->soldierSprite.setColor(Color::Red);
                    }
                    else if (s[min_x][min_y]->side == atk) {
                        s[min_x][min_y]->soldierSprite.setColor(Color::Blue);
                    }
                }
                return 1;
            }
            else
                return 0;
        }
    void Super_soldier::move(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base) {
        if (is_moved == 1||move_tag=='Q'||move_tag=='q') { return; }//已经移动了，无需再移动
        if ((move_tag=='a'||move_tag=='A' )&& s[pos[0]][pos[1] - 1] == empty1 && (pos[0]) < ROW_MAX && (pos[1] - 1) < COL_MAX && (pos[0]) >= 0 && (pos[1] - 1) >= 0) {

            MOVE_LEFT
               // soldierSprite.move(-33.33333333f, 0.f);
            is_moved = 1;


        }
        else if ((move_tag == 'd' || move_tag == 'D') && s[pos[0]][pos[1] + 1] == empty1 && (pos[0]) < ROW_MAX && (pos[1] + 1) < COL_MAX && (pos[0]) >= 0 && (pos[1] + 1) >= 0) {

            MOVE_RIGHT
              //  soldierSprite.move(33.33333333f, 0.f);
            is_moved = 1;

        }
        else if ((move_tag == 'w' || move_tag == 'W') && s[pos[0] - 1][pos[1]] == empty1 && (pos[0] - 1) < ROW_MAX && pos[1] < COL_MAX && (pos[0] - 1) >= 0 && pos[1] >= 0) {

            MOVE_UP
               // soldierSprite.move(0.f, -33.33333333f);
            is_moved = 1;

        }
        else if ((move_tag == 's' || move_tag == 'S') && s[pos[0] + 1][pos[1]] == empty1 && (pos[0] + 1) < ROW_MAX && pos[1] < COL_MAX && (pos[0] + 1) >= 0 && pos[1] >= 0) {

            MOVE_DOWN
               // soldierSprite.move(0.f, 33.33333333f);
            is_moved = 1;
        }
        
        is_moved = 1;
        Super_soldier::atk_enemy(s, row, col, empty1, atk_base, def_base);
    }

    int Super_soldier::atk_enemy(Soldier***& s, int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base) {
        int is_atk=0;
        int i, j;
        int damage;
        if (s[pos[0]][pos[1]]->side == atk)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->attack_range) >= row)
            {
                imax = row - 1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->attack_range) >= col)
            {
                jmax = col - 1;
            }

            for (i = imin; i <= imax; ++i)
            {

                for (j = jmin; j <= jmax; ++j)
                {
                    if (s[i][j]->side == def) {
                        is_atk = 1;
                        if ((damage = damage_calculate(s[i][j], s[pos[0]][pos[1]])) > s[i][j]->hp)
                        {
                            s[i][j] = empty1;//攻击直接致死
                            s[i][j]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                        }
                        else
                        {
                            s[i][j]->hp -= damage;//攻击不至死，减一定的血量
                            if (s[i][j]->side == def) {
                                s[i][j]->soldierSprite.setColor(Color::Red);
                            }
                            else if (s[i][j]->side == atk) {
                                s[i][j]->soldierSprite.setColor(Color::Blue);
                            }
                        }
                    }
                }
            }
        }
        else if (s[pos[0]][pos[1]]->side == def)
        {
            int imin, imax;
            int jmin, jmax;
            if ((imin = pos[0] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                imin = 0;
            }
            if ((imax = pos[0] + s[pos[0]][pos[1]]->attack_range) >= row)
            {
                imax = col - 1;
            }
            if ((jmin = pos[1] - s[pos[0]][pos[1]]->attack_range) < 0)
            {
                jmin = 0;
            }
            if ((jmax = pos[1] + s[pos[0]][pos[1]]->attack_range) >= col)
            {
                jmax = col - 1;
            }
            for (i = imin; i <= imax; ++i)
            {
                for (j = jmin; j <= jmax; ++j)
                {
                    if (s[i][j]->side == atk) {
                        is_atk = 1;
                        if ((damage = damage_calculate(s[i][j], s[pos[0]][pos[1]])) > s[i][j]->hp)
                        {
                            s[i][j] = empty1;//攻击直接致死
                            s[i][j]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                        }
                        else
                        {
                            s[i][j]->hp -= damage;//攻击不至死，减一定的血量
                            if (s[i][j]->side == def) {
                                s[i][j]->soldierSprite.setColor(Color::Red);
                            }
                            else if (s[i][j]->side == atk) {
                                s[i][j]->soldierSprite.setColor(Color::Blue);
                            }
                        }
                    }
                }
            }
        }
        return is_atk;
    }

    //骑兵的移动，采用递归处理，实现移动三步
    void Knight::move(Soldier***& s,int row, int col, Soldier* empty1, Soldier*& atk_base, Soldier*& def_base)
    {
        if (is_moved == 1)
            return;

        if (atk_enemy(s,row, col,empty1, atk_base, def_base))
        {
            is_moved = 1;
            return;
        }
        if (g_step == 3)
        {
            is_moved = 1;
            return;
        }
        else
        {
            find_nearest_enemy(s,row, col,atk_base,def_base);
            if (g_nearest_row < pos[0])     //如果敌人在上方
            {
                if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1) //如果上一格是空的，则移到上一格
                {
                    MOVE_UP
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);

                }
                else if (g_nearest_col < pos[1])         //如果上一格有友军
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //左边空的，则移到左边
                    {
                        MOVE_LEFT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //若右边空着，则移到右边
                {
                    MOVE_RIGHT
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);
                }
            }
            else if (g_nearest_row > pos[0])  //如果敌人在下方
            {
                if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //如果下一格是空的，则移到下一格
                {
                    MOVE_DOWN
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);
                }
                else if (g_nearest_col < pos[1])         //如果下一格有友军
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //左边空的，则移到左边
                    {
                        MOVE_LEFT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
                else if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)  //若右边空着，则移到右边
                {
                    MOVE_RIGHT
                        g_step++;
                    move(s,row, col, empty1, atk_base, def_base);
                }
            }
            else if (g_nearest_row == pos[0])     //如果在同一行
            {
                if (g_nearest_col < pos[1])         //
                {
                    if ((pos[1] != 0) && s[pos[0]][pos[1] - 1] == empty1)   //左边空的，则移到左边
                    {
                        MOVE_LEFT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //上边空的，则移到上边
                    {
                        MOVE_UP
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //下边空的，则移到下边
                    {
                        MOVE_DOWN
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
                else if (g_nearest_col > pos[1])
                {
                    if ((pos[1] != col - 1) && s[pos[0]][pos[1] + 1] == empty1)   //右边空的，则移到右边
                    {
                        MOVE_RIGHT
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != 0) && s[pos[0] - 1][pos[1]] == empty1)   //上边空的，则移到上边
                    {
                        MOVE_UP
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                    else if ((pos[0] != row - 1) && s[pos[0] + 1][pos[1]] == empty1)   //下边空的，则移到下边
                    {
                        MOVE_DOWN
                            g_step++;
                        move(s,row, col, empty1, atk_base, def_base);
                    }
                }
            }
            //        if(g_step==3)
            //            atk_enemy(s,row,col);

        }
        g_step = 0;
    }

    //弓箭手攻击函数，攻击范围1~3
    int Bowman::atk_enemy(Soldier***& s,int row, int col, Soldier* empty1, Soldier*&atk_base, Soldier*&def_base)
    {
        uchar damage;
        find_nearest_enemy(s,row, col, atk_base, def_base);
       // cout << g_min_distance<<endl;
        if (g_min_distance <= 3)
        {
            //cout << damage_calculate(s[g_nearest_row][g_nearest_col], s[pos[0]][pos[1]]) << endl;
            if ((damage = damage_calculate(s[g_nearest_row][g_nearest_col],  s[pos[0]][pos[1]])) > s[g_nearest_row][g_nearest_col]->hp)
            {

                s[g_nearest_row][g_nearest_col] = empty1;
                s[g_nearest_row][g_nearest_col]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
            }
            else
            {
                s[g_nearest_row][g_nearest_col]->hp -= damage;
                if (s[g_nearest_row][g_nearest_col]->side == def) {
                    s[g_nearest_row][g_nearest_col]->soldierSprite.setColor(Color::Red);
                }else
                  if (s[g_nearest_row][g_nearest_col]->side == atk) {
                        s[g_nearest_row][g_nearest_col]->soldierSprite.setColor(Color::Blue);
                    }
            }
            return 1;
        }
        else
            return 0;
    }



    void Soldier::generate_soldier(Soldier***& s,int row, int col, Soldier* empty1) {
        //表示基地的可以生成士兵的范围
        if ((min_generate_row = (pos[0] - GENERATE_RANGE)) <= 0) {
            min_generate_row = 0;
        }
        if ((min_generate_col = (pos[1] - GENERATE_RANGE)) <= 0) {
            min_generate_col = 0;
        }
        if ((max_generate_row = (pos[0] + GENERATE_RANGE)) >= ROW_MAX - 1) {
            max_generate_row = ROW_MAX - 1;
        }
        if ((max_generate_col = (pos[1] + GENERATE_RANGE)) >= COL_MAX - 1) {
            max_generate_col = COL_MAX - 1;
        }
        srand(time(NULL));
        int tag;
        //char pos1[2];
        int pos1[2];
        for (int i = min_generate_row; i <= max_generate_row; i++) {
            for (int j = min_generate_col; j <= max_generate_col; j++) {
                if (s[i][j] != s[pos[0]][pos[1]]) {//不与基地重合
                    if (s[i][j] == empty1) {

                        if (rand() % 20== 1) {//在empty处生成该点的概率有5%
                            pos1[0] = i; pos1[1] = j;
                            if (total_bowman_num > 0 || total_footman_num > 0 || total_knight_num > 0) {

                                generate_bowman_rate = 100 * (total_bowman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_footman_rate = generate_bowman_rate + 100 * (total_footman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_knight_rate = generate_footman_rate + 100 * (total_knight_num) / (total_bowman_num + total_footman_num + total_knight_num);

                                tag = rand() % generate_knight_rate + 1;

                                if (tag > 0 && tag <= generate_bowman_rate) {

                                    s[i][j] = new Bowman(bowman, this->side, pos1);
                                    total_bowman_num--;
                                }
                                else if (tag > generate_bowman_rate && tag <= generate_footman_rate) {

                                    s[i][j] = new Footman(footman, this->side, pos1);
                                    total_footman_num--;

                                }
                                else if (tag > generate_footman_rate && tag <= generate_knight_rate) {

                                    s[i][j] = new Knight(knight, this->side, pos1);
                                    total_knight_num--;

                                }


                            }
                        }



                    }
                }
            }
        }
    }
    void Base::generate_soldier(Soldier***& s, int row, int col, Soldier* empty1) {
        //表示基地的可以生成士兵的范围


        if ((min_generate_row = (pos[0] - GENERATE_RANGE)) <= 0) {
            min_generate_row = 0;
        }
        if ((min_generate_col = (pos[1] - GENERATE_RANGE)) <= 0) {
            min_generate_col = 0;
        }
        if ((max_generate_row = (pos[0] + GENERATE_RANGE)) >= ROW_MAX - 1) {
            max_generate_row = ROW_MAX - 1;
        }
        if ((max_generate_col = (pos[1] + GENERATE_RANGE)) >= COL_MAX - 1) {
            max_generate_col = COL_MAX - 1;
        }
        srand(time(NULL));
        int tag;
        //char pos1[2];
        int pos1[2];
        for (int i = min_generate_row; i <= max_generate_row; i++) {
            for (int j = min_generate_col; j <= max_generate_col; j++) {
                if (s[i][j] != s[pos[0]][pos[1]]) {//不与基地重合
                    if (s[i][j] == empty1) {
                   
                        if (rand() % 20== 1) {//在empty处生成该点的概率有5%
                            pos1[0] = i; pos1[1] = j;
                            if (total_bowman_num > 0 || total_footman_num > 0 || total_knight_num > 0) {

                                generate_bowman_rate = 100 * (total_bowman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_footman_rate = generate_bowman_rate + 100 * (total_footman_num) / (total_bowman_num + total_footman_num + total_knight_num);
                                generate_knight_rate = generate_footman_rate + 100 * (total_knight_num) / (total_bowman_num + total_footman_num + total_knight_num);

                                tag = rand() % generate_knight_rate + 1;

                                if (tag > 0 && tag <= generate_bowman_rate) {

                                    s[i][j] = new Bowman(bowman, this->side, pos1);
                                    total_bowman_num--;
                                
                                        
                                }
                                else if (tag > generate_bowman_rate && tag <= generate_footman_rate) {

                                    s[i][j] = new Footman(footman, this->side, pos1);
                                    total_footman_num--;
                                   
                                }
                                else if (tag > generate_footman_rate && tag <= generate_knight_rate) {

                                    s[i][j] = new Knight(knight, this->side, pos1);
                                    total_knight_num--;
                        
                                }


                            }
                        }



                    }
                }
            }
        }
    }
    int Base::atk_enemy(Soldier***& s,int row, int col, Soldier* empty1, Soldier*&atk_base, Soldier*&def_base) {
        //表示基地可以攻击的范围
        if ((min_atk_row = (pos[0] - BASE_ATK_RANGE)) <= 0) {
            min_atk_row = 0;
        }
        if ((min_atk_col = (pos[1] - BASE_ATK_RANGE)) <= 0) {
            min_atk_col = 0;
        }
        if ((max_atk_row = (pos[0] + BASE_ATK_RANGE)) >= ROW_MAX - 1) {
            max_atk_row = ROW_MAX - 1;
        }
        if ((max_atk_col = (pos[1] + BASE_ATK_RANGE)) >= COL_MAX - 1) {
            max_atk_col = COL_MAX - 1;
        }
        uchar damage, min_hp = 230, min_x = 50, min_y = 50, can_atk = 0;
        for (int i = min_atk_row; i <= max_atk_row; i++) {
            for (int j = min_atk_row; j <= max_atk_row; j++) {
                if (s[pos[0]][pos[1]] != s[i][j]) {
                    if (s[i][j] != empty1 ) {
                        if (s[i][j]->side != side && (s[i][j]->side != mid)) {
                            can_atk = 1;
                            min_hp = s[i][j]->hp;
                            if ((damage = damage_calculate(s[i][j], s[pos[0]][pos[1]])) > min_hp)
                            {
                                s[i][j] = empty1;
                                s[i][j]->soldierSprite.setPosition(Vector2f(1000.0f, 1000.0f));
                            }
                            else
                            {
                                s[i][j]->hp -= damage;
                            }
                        }
                    }
                }
            }
        }
        if (can_atk == 1) { return 1; }
        else return 0;
    }


    Base::Base(soldier_type c_type, war_side c_side, int c_pos[]) {

        type = c_type;
        side = c_side;
        price = 0;
        attack = 5;
        defence = 1;
        crit_rate = 15;
        hp = 200;
        attack_range = 3;
        move_range = 0;
        is_moved = 0;
    
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (side == atk) {
            soldierTex.loadFromFile("Textures/atk_base.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (side == def) {
            soldierTex.loadFromFile("Textures/def_base.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }

    }

    //弓箭手构造函数
    Bowman::Bowman(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 5;
        type = c_type;
        side = c_side;
        price = BOWMAN_PRICE;
        attack = 15;
        defence = 1;
        crit_rate = 10;
        hp = 90;
        attack_range = 3;
        move_range = 1;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
            soldierTex.loadFromFile("Textures/atk_bowman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_bowman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

    //步兵构造函数
    Footman::Footman(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 5;
        type = c_type;
        side = c_side;
        price = FOOTMAN_PRICE;
        attack = 15;
        defence = 3;
        crit_rate = 5;
        hp = 100;
        attack_range = 1;
        move_range = 1;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
          soldierTex.loadFromFile("Textures/atk_footman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_footman.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

    //骑兵构造函数
    Knight::Knight(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 10;
        type = c_type;
        side = c_side;
        price = KNIGHT_PRICE;
        attack = 18;
        defence = 5;
        crit_rate = 8;
        hp = 120;
        attack_range = 1;
        move_range = 3;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
          soldierTex.loadFromFile("Textures/atk_knight.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_knight.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
           soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

    Soldier::Soldier() {
        type = normal;
        side = mid;
        price = 0;
        attack = 0;
        defence = 0;
        crit_rate = 0;
        hp = 0;
        attack_range = 0;
        move_range = 0;
        is_moved = 0;
        generate_footman_rate = 0, generate_bowman_rate = 0, generate_knight_rate = 0;
        total_footman_num = 0, total_bowman_num = 0, total_knight_num = 0;
        min_generate_row = 0, min_generate_col = 0, max_generate_row = 0, max_generate_col = 0;
        min_atk_row = 0, min_atk_col = 0, max_atk_row = 0, max_atk_col = 0;
        // char pos[2]={0,0}; //坐标(y,x)y:pos[0],x:pos[1]
        pos[0] = 0; //坐标(y,x)y:pos[0],x:pos[1]
        pos[1] = 0;


        int pos_base_init[2] = { 0,0 };
        // empty1 = new Soldier;
        // block = new Soldier;
        // atk_base = new Base(base, atk, pos_base_init);
        // def_base = new Base(base, def, pos_base_init);
        g_nearest_row = 0, g_nearest_col = 0, g_step = 0, g_min_distance = 0;
       
    
    }

    Super_soldier::Super_soldier(soldier_type c_type, war_side c_side, int c_pos[])
    {
        view_range = 30;
        type = c_type;
        side = c_side;
        price = 0;
        attack = 25;
        defence = 10;
        crit_rate = 15;
        hp = 150;
        attack_range = 1;
        move_range = 1;
        is_moved = 0;
        //strcpy(pos,c_pos);
        pos[0] = c_pos[0];
        pos[1] = c_pos[1];
        if (this->side == atk) {
            soldierTex.loadFromFile("Textures/atk_super.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
        else  if (this->side == def) {
            soldierTex.loadFromFile("Textures/def_super.png");
            soldierSprite.setTexture(soldierTex);
            soldierSprite.setScale(Vector2f(0.22222222f, 0.22222222f));
            soldierSprite.setPosition(Vector2f(33.33333333 * pos[1], 33.33333333 * pos[0]));
        }
    }

